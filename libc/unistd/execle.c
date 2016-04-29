/*
 *	libc/unistd/execle.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

int execle(const char * pathname, char * arg0, ...)
{
	char ** env = &arg0;

	while (!*env)
		env++;

	return execve(pathname,&arg0,env);
}
