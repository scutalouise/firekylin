/*
 *    fs/minix/bitmap.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

static int find_bit(char *addr, int size)
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < 8; j++)
			if (!((*addr) & (1 << j)))
				return (i * 8 + j);
		addr++;
	}
	return -1;
}

int test_bit(char *addr, int bit)
{
	return *(addr + bit / 8) & (1 << bit % 8);
}

static void set_bit(char *addr, int bit)
{
	*(addr + bit / 8) = *(addr + bit / 8) | (1 << (bit % 8));
}

static void clr_bit(char *addr, int bit)
{
	*(addr + bit / 8) = *(addr + bit / 8) & (~(1 << (bit % 8)));
}

int minix1_free_block(dev_t dev, int block)
{
	struct buffer * buf;
	struct super *super = get_super(dev);

	if (block < super->s_first_data_zone || block > super->s_zones)
		panic("block too big %x", block);
	buf = bread(dev, block);
	if (buf->b_count != 1)
		panic("block is using");
	brelse(buf);
	buf = bread(dev, 2 + super->s_imap_blocks + block / (8 * 1024));
	clr_bit(buf->b_data, block % (8 * 1024));
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_free_inode(dev_t dev, ino_t ino)
{
	struct buffer * buf;
	struct super *super = get_super(dev);

	if (ino<1 || ino > super->s_inodes)
		panic("block too big %x", ino);

	buf = bread(dev, 2 + ino / (8 * 1024));
	clr_bit(buf->b_data, ino % (8 * 1024));
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_alloc_block(dev_t dev)
{
	struct buffer *bh;
	struct super *super;
	int res, tmp;

	super=get_super(dev);
	for(int i=0;i<super->s_zmap_blocks;i++){
		bh=bread(dev,2+super->s_imap_blocks+i);
		if(!bh)
			panic("alloc_inode: cann't inode block");

		tmp=find_bit(bh->b_data,1024);

		res=i*1024*8+tmp;
		if(tmp>super->s_zones){
			brelse(bh);
			put_super(super);
			return 0;
		}
		set_bit(bh->b_data,tmp);
		bh->b_flag|=B_DIRTY;
		brelse(bh);
		res+=super->s_first_data_zone;
		put_super(super);
		return res;
	}
	put_super(super);
	return 0;
}

struct inode * minix1_alloc_inode(dev_t dev)
{
	struct buffer *bh;
	struct super  *super;
	struct inode  *inode;
	struct task   *current;
	struct fs_operation *fs_op;
	ino_t res;
	int tmp;

	super=get_super(dev);
	for(int i=0;i<super->s_imap_blocks;i++){
		bh=bread(dev,2+i);
		if(!bh)
			panic("alloc_inode: cann't inode block");

		tmp=find_bit(bh->b_data,1024);

		res=i*1024*8+tmp;
		if(tmp>super->s_inodes){
			brelse(bh);
			put_super(super);
			return NULL;
		}

		set_bit(bh->b_data,tmp);
		bh->b_flag|=B_DIRTY;
		brelse(bh);
		fs_op=super->s_op;
		put_super(super);

		inode=iget(dev,res);
		if(!inode){
			minix1_free_inode(dev,res);
			return NULL;
		}

		current=CURRENT_TASK();
		inode->i_nlink=1;
		inode->i_uid=current->uid;
		inode->i_gid=current->gid;
		inode->i_size=0;
		inode->i_atime=inode->i_mtime=inode->i_ctime=current_time();
		inode->i_op=fs_op;
		memset(inode->i_zone,0,4*NR_ZONE);
		inode->i_wait=NULL;
		return inode;
	}
	put_super(super);
	return NULL;
}
