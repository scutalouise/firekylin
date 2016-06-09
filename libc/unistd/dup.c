/*
 *	libc/unistd/dup.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <errno.h>

int dup(int fd)
{
	return fcntl(fd,F_DUPFD,0);
}
