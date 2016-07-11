/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/param.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>

struct inode            inode_table[NR_INODE];
struct inode          * root_inode;
sleeplock_t             inode_table_lock;

#define lock_inode_table()	require_lock(&inode_table_lock);
#define unlock_inode_table()	release_lock(&inode_table_lock);

struct inode * iget(dev_t dev, ino_t ino)
{
	struct super * super;
	struct inode * inode;

	lock_inode_table();
repeat:
	if (!dev)
		goto no_dev;
	inode = inode_table;
	while (inode < inode_table + NR_INODE) {
		if (inode->i_dev == dev && inode->i_ino == ino) {
			inode->i_count++;
			unlock_inode_table();
			ilock(inode);
			return inode;
		}
		inode++;
	}
no_dev:
	inode = inode_table;
	while (inode < inode_table + NR_INODE) {
		if (!inode->i_count) {
			inode->i_count++;
			unlock_inode_table();
			lock_inode(inode);
			if(inode->i_flag&I_DIRTY){
				inode->i_op->inode_write(inode);
				unlock_inode(inode);
				goto repeat;
			}
			inode->i_dev = dev;
			inode->i_ino = ino;
			if (dev){
				super=get_super(dev);
				inode->i_op=super->s_op;
				put_super(super);
				inode->i_op->inode_read(inode);
			}
			return inode;
		}
		inode++;
	}
	unlock_inode_table();
	return NULL;
}

void iput(struct inode * inode)
{
	if (!inode)
		return;

	if (inode->i_count <= 0)
		panic("put_inode:put free inode");

	if (--inode->i_count == 0 && inode->i_dev) {
		inode->i_op->inode_write(inode);
	}
	iunlock(inode);
}

extern dev_t mount_inode(struct inode *inode);

struct inode *namei(char *filepath, char **basename)
{
	struct inode *inode;
	char name[MAX_NAME_LEN + 1];

	if (*filepath == '/') {
		filepath++;
		inode = idup(root_inode);
	} else
		inode = idup((CURRENT_TASK() )->pwd);

	while (*filepath) {
		if(basename)
			*basename=filepath;

		for (int i = 0; i < MAX_NAME_LEN; i++) {
			if (*filepath == 0 || *filepath == '/') {
				name[i] = 0;
				break;
			}
			name[i] = *filepath++;
		}
		if (!*filepath && basename)
			return inode;

		if (*filepath == '/')
			filepath++;

		if( (inode !=root_inode) && inode->i_ino==1 &&
		    name[0]=='.' &&
		    name[1]=='.' &&
		    name[2]==0){
			struct super *super=get_super(inode->i_dev);
			iput(inode);
			inode=idup(super->s_imount);
			put_super(super);
		}
		if (inode->i_op->lookup(inode, name,&inode)) {
			return NULL;
		}
		if (inode->i_flag & I_MOUNT){
			dev_t tmp=mount_inode(inode);
			iput(inode);
			inode=iget(tmp,1);
		}
	}
	return inode;
}

void sync_inode()
{
	struct inode *inode = inode_table;

	while (inode < inode_table + NR_INODE) {
		ilock(inode);
		if (inode->i_flag & I_DIRTY)
			inode->i_op->inode_write(inode);
		iunlock(inode);
		inode++;
	}
}
