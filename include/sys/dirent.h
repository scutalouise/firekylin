/*
 *    include/sys/dirent.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

struct dirent{
	ino_t  d_ino;
	off_t  d_off;
	size_t d_reclen;
	char   d_name[];
};

#endif
