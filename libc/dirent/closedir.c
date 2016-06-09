/*
 *	libc/dirent/closedir.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/dirent.h>
#include <stdlib.h>
#include <errno.h>

int closedir(DIR * dir)
{
	int fd;

	if (!dir) {
		errno = EBADF;
		return -1;
	}

	fd = dir->dd_fd;
	free(dir);

	return close(fd);
}
