/*
 *	libc/unistd/execl.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

int execl(const char * pathname, char * arg0, ...)
{
	return execve(pathname,&arg0,environ);
}
