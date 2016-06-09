/*
 *	libc/dirent/readdir.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static struct dirent _res_dirent;

struct dirent * readdir(DIR * dir)
{
	if (!dir) {
		errno = EBADF;
		return NULL;
	}

	if(read(dir->dd_fd,(char*)&_res_dirent,sizeof(struct dirent))<=0)
		return NULL;

	return &_res_dirent;
}
