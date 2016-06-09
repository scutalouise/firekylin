/*
 *    include/sys/dirent.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

#define MAX_MANE_LEN	255
struct dirent{
	ino_t  d_ino;
	size_t d_reclen;
	char   d_name[MAX_MANE_LEN+1];
};

#endif
