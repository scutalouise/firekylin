/*
 *	libc/unistd/wait.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

int wait(long *status)
{
	return waitpid(0,status,0);
}
