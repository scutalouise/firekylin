/*
 *	libc/unistd/execve.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <errno.h>

static inline 
__syscall3(int, exec, const char*, path, char **, argv,char **, envp) ;

int execve(const char *path, char **argv, char **envp)
{
	return exec(path, argv, envp);
}
