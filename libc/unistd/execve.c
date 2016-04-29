/*
 *	libc/unistd/execve.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

__syscall3(int, execve, const char*, filename, char **, argv,char **, envp) ;
