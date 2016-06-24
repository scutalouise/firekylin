/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "proc.h"

int proc_read_inode(struct inode * inode)
{
	return 0;
}

int proc_write_inode(struct inode * inode)
{
	return 0;
}

int proc_mknod(struct inode *dir_inode, char *name, mode_t mode,
		dev_t dev)
{
	return -EPERM;
}

int proc_mkdir(struct inode *dir_inode,char *name,mode_t mode)
{
	return -EPERM;
}

int proc_link(struct inode *dir_inode,char *name, struct inode *inode)
{
	return -EPERM;
}

int proc_unlink(struct inode *dir_inode, char *name)
{
	return -EPERM;
}

int proc_rmdir(struct inode *dir_inode, char *name)
{
	return -EPERM;
}

int proc_rename(struct inode *inode, char *old, char *new)
{
	return -EPERM;
}
