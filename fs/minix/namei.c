/*
 *    fs/minix/inode.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

static struct buffer * find_entry(struct inode *dir_inode, char *filename,
		struct dir_entry **res_de)
{
	struct buffer *buf;
	struct inode *inode = NULL;
	struct dir_entry *de;

	for (int i = 0; i < 7 + 512; i++) {
		buf = bread(dir_inode->i_dev, minix1_rbmap(dir_inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct dir_entry *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct dir_entry); j++) {

			if (i * 1024 + j * sizeof(struct dir_entry)
					> dir_inode->i_size) {

				brelse(buf);
				*res_de = NULL;
				return NULL;
			}

			if (!strncmp(de->name, filename, NAME_LEN)) {
				*res_de = de;
				return buf;
			}
			de++;
		}
		brelse(buf);
	}
	*res_de = NULL;
	return NULL;
}

static int add_entry(struct inode *inode, char *name,ino_t ino)
{
	struct buffer *buf;
	struct dir_entry *de;
	int size=0;

	if (!inode)
		panic("find_entry:inode is NULL");

	for (int i = 0; i < 7 + 512; i++) {

		buf = bread(inode->i_dev, minix1_wbmap(inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct dir_entry *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct dir_entry); j++) {
			if (size<inode->i_size && de->ino) {
				size += sizeof(struct dir_entry);
				de++;
				continue;
			}

			strncpy(de->name,name,NAME_LEN);
			de->ino=ino;
			buf->b_flag |= B_DIRTY;

			size += sizeof(struct dir_entry);

			if (size > inode->i_size) {
				inode->i_size = size;
				inode->i_flag |= I_DIRTY;
			}

			brelse(buf);
			return 0;
		}
		brelse(buf);
		return 1;
	}
}

int count_entry(struct inode *inode)
{
	struct buffer *buf;
	struct dir_entry *de;
	int count=0;

	for (int i = 0; i < 7 + 512; i++) {
		buf = bread(inode->i_dev, minix1_rbmap(inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct dir_entry *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct dir_entry); j++) {

			if (i * 1024 + j * sizeof(struct dir_entry)
					> inode->i_size) {

				brelse(buf);
				return count;
			}

			if(!de->ino){
				de++;
				continue;
			}
			count++;
			de++;
		}
		brelse(buf);
	}
	return count;
}

int minix1_look_up(struct inode *dir_inode, char *filename,
		struct inode **res_inode)
{
	struct buffer *buf;
	struct inode *inode;
	struct dir_entry *de;
	int ino;

	if (filename[0] == '.' && filename[1] == 0) {
		*res_inode = dir_inode;
		return 0;
	}

	buf = find_entry(dir_inode, filename, &de);

	if (!buf) {
		iput(dir_inode);
		*res_inode = NULL;
		return 1;

	}

	if (de->ino == dir_inode->i_ino) {
		brelse(buf);
		*res_inode = dir_inode;
		return 0;
	}

	inode = iget(dir_inode->i_dev, de->ino);
	if (!inode) {
		brelse(buf);
		*res_inode = NULL;
		return 1;
	}
	brelse(buf);
	iput(dir_inode);
	*res_inode = inode;
	return 0;
}

int minix1_mknod(struct inode *dir_inode, char *name, mode_t mode, dev_t dev )
{
	struct buffer *buf;
	struct dir_entry *de;
	struct inode *new_inode;

	if ((buf = find_entry(dir_inode, name, &de))) {
		brelse(buf);
		return -EEXIST;
	}

	if (!(new_inode=minix1_alloc_inode(dir_inode->i_dev))){
		return -EAGAIN;
	}
	new_inode->i_mode=mode;
	if(S_ISCHR(mode) || S_ISBLK(mode))
		new_inode->i_rdev=dev;

	if ((add_entry(dir_inode, name,new_inode->i_ino))) {
		iput(new_inode);
		minix1_free_inode(dir_inode->i_dev, new_inode->i_ino);
		return -1;
	}
	new_inode->i_flag|=I_DIRTY;
	iput(new_inode);
	return 0;
}

int minix1_mkdir(struct inode *dir_inode,char *name,mode_t mode)
{
	struct buffer *buf;
	struct dir_entry *de;
	struct inode *inode;
	int res;

	if ((buf = find_entry(dir_inode, name, &de))) {
		brelse(buf);
		return -EEXIST;
	}

	if(!(inode=minix1_alloc_inode(dir_inode->i_dev)))
		return -EAGAIN;
	inode->i_mode=mode;
	inode->i_flag|=I_DIRTY;
	iput(inode);
	add_entry(dir_inode,name,inode->i_ino);
	minix1_link(inode,".",inode);
	minix1_link(inode,"..",dir_inode);
	return 0;
}

int minix1_link(struct inode *dir_inode,char *name, struct inode *inode)
{
	struct buffer *buf;
	struct dir_entry *de;

	if((buf=find_entry(dir_inode,name,&de))){
		brelse(buf);
		return -EEXIST;
	}

	inode->i_nlink++;
	inode->i_flag|=I_DIRTY;
	return add_entry(dir_inode,name,inode->i_ino);
}

int minix1_unlink(struct inode *dir_inode, char *name)
{
	struct dir_entry *de;
	struct buffer *buf;
	struct inode *del_inode;

	buf = find_entry(dir_inode, name, &de);
	if (!buf)
		return -ENOENT;

	del_inode = iget(dir_inode->i_dev, de->ino);

	if (!del_inode) {
		brelse(buf);
		return -EAGAIN;
	}
	if (del_inode->i_count != 1) {
		iput(del_inode);
		brelse(buf);
		return -EBUSY;
	}
	if (S_ISDIR(del_inode->i_mode)){
		iput(del_inode);
		brelse(buf);
		return -EISDIR;
	}

	del_inode->i_nlink--;
	del_inode->i_flag|=I_DIRTY;
	iput(del_inode);
	de->ino = 0;
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_rmdir(struct inode *dir_inode, char *name)
{
	struct dir_entry *de;
	struct buffer *buf;
	struct inode *del_inode;

	buf = find_entry(dir_inode, name, &de);
	if (!buf)
		return -ENOENT;

	del_inode = iget(dir_inode->i_dev, de->ino);

	if (!del_inode) {
		brelse(buf);
		return -EAGAIN;
	}
	if (del_inode->i_count != 1) {
		iput(del_inode);
		brelse(buf);
		return -EBUSY;
	}
	if (!S_ISDIR(del_inode->i_mode)){
		iput(del_inode);
		brelse(buf);
		return -ENOTDIR;
	}

	minix1_unlink(del_inode,".");
	minix1_unlink(del_inode,"..");
	brelse(buf);
	iput(del_inode);
	minix1_unlink(dir_inode,name);
	return 0;
}

int minix1_rename(struct inode *inode, char *old, char *new)
{
	struct dir_entry *de;
	struct buffer *buf;

	buf = find_entry(inode, old, &de);
	if (!buf)
		return -ENOENT;
	strncpy(de->name, new, NAME_LEN);
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}
