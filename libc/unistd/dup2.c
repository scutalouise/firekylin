/*
 *	libc/unistd/dup2.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

int dup2(int fd,int fd2)
{
	return fcntl(fd,F_DUPFD,fd2);
}
