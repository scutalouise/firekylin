/*
 *	libc/unistd/lseek.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

int lseek(int fd,long off,int where)
{
	return fcntl(fd,F_SEEKSET+where,off);
}
