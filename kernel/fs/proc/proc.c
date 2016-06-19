/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "proc.h"

struct fs_operation proc_operation={
	proc_read_super,
	proc_write_super,
	proc_read_inode,
	proc_write_inode,
	proc_lookup,
	proc_mknod,
	proc_mkdir,
	proc_link,
	proc_unlink,
	proc_rmdir,
	proc_rename,
	proc_file_read,
	proc_file_readdir,
	proc_file_write
};


int proc_file_write(struct file *file, char * buf, size_t size)
{
	return -EIO;
}

