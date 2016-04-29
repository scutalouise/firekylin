/*
 *	libc/unistd/execv.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

int execv(const char * pathname, char ** argv)
{
	return execve(pathname,argv,environ);
}
