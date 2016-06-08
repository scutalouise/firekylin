/*
 *    fs/minix/file.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

int minix1_file_read(struct inode *inode, char * buf, size_t size, off_t off,
		int rw_flag)
{
	struct buffer *bh;
	int chars, left;

	if (off >= inode->i_size)
		return 0;
	if (off + size >= inode->i_size)
		size = inode->i_size - off;

	left = size;
	while (left > 0) {
		bh = bread(inode->i_dev, minix1_rbmap(inode, off / 1024));
		if (!bh) {
			panic("read file error");
		}
		chars = min(left, 1024 - off % 1024);
		memcpy(buf, bh->b_data + off % 1024, chars);
		brelse(bh);
		buf += chars;
		off += chars;
		left -= chars;
	}
	return size - left;
}

int minix1_file_write(struct inode *inode, char * buf, size_t size, off_t off,
		int rw_flag)
{
	struct buffer *bh;
	int left, chars;

	left = size;
	while (left) {
		bh = bread(inode->i_dev, minix1_wbmap(inode, off / 1024));
		if (!bh) {
			panic("write file error");
		}
		chars = min((1024 - off % 1024), left);
		memcpy(bh->b_data + off % 1024, buf, chars);
		off += chars;
		left -= chars;
		bh->b_flag|=B_DIRTY;
		brelse(bh);
	}
	return size - left;
}

int minix1_file_truncate(struct inode *inode)
{
//	struct buffer *buf;
//	unsigned short *p;
//
//	if(!(S_ISREG(inode->i_mode)|| S_ISDIR(inode->i_mode)))
//		return 0;
//	for(int i=0;i<7;i++){
//		if(inode->i_zone[i]){
//			minix1_free_block(inode->i_dev,inode->i_zone[i]);
//			inode->i_zone[i]=0;
//		}
//	}
//
//	if(inode->i_zone[7]){
//		buf=bread(inode->i_dev,inode->i_zone[7]);
//		p=(unsigned short *)buf->b_data;
//		for(int i=0;i<512;i++,p++){
//			if(*p){
//				minix1_free_block(inode->i_dev,*p);
//			}
//		}
//		brelse(buf);
//		minix1_free_block(inode->i_dev,inode->i_zone[7]);
//		inode->i_zone[7]=0;
//	}
//	inode->i_size=0;
//	inode->i_mtime=inode->i_ctime=current_time();
//	inode->i_flag|=I_DIRTY;
	return 0;
}
