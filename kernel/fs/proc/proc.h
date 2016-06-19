/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _PROC_H
#define _PROC_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/fs.h>
#include <firekylin/string.h>
#include <firekylin/bitmap.h>

extern int proc_read_super(struct super *super);
extern int proc_write_super(struct super *super);
extern int proc_read_inode(struct inode * inode);
extern int proc_write_inode(struct inode * inode);
extern int proc_lookup(struct inode *dir_inode, char *filename,
		struct inode **res_inode);
extern int proc_mknod(struct inode *dir_inode, char *name, mode_t mode,
		dev_t dev);
extern int proc_mkdir(struct inode *dir_inode,char *name,mode_t mode);
extern int proc_link(struct inode *dir_inode,char *name, struct inode *inode);
extern int proc_unlink(struct inode *dir_inode, char *name);
extern int proc_rmdir(struct inode *dir_inode, char *name);
extern int proc_rename(struct inode *inode, char *old, char *new);
extern int proc_file_read(struct file *file, char * buf, size_t size);
extern int proc_file_readdir(struct file *file, char * buf, size_t size);
extern int proc_file_write(struct file *file, char * buf, size_t size);


#endif
