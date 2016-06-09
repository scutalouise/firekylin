/*
 *	libc/dirent/opendir.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/dirent.h>
#include <stdlib.h>
#include <errno.h>

DIR * opendir(char * dirname)
{
	struct stat statbuf;
	DIR *dir;
	int  fd;

	if ((fd = open(dirname, O_READ)) < 0)
		return NULL;

	if (fstat(fd, &statbuf) < 0 ||
	    !S_ISDIR(statbuf.st_mode) ||
	    !(dir =malloc(sizeof(DIR)))) {
		close(fd);
		return NULL;
	}

	dir->dd_fd = fd;

	return dir;
}
