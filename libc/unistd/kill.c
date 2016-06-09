/*
 *	libc/unistd/kill.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <errno.h>

int kill(pid_t pid, int signo)
{
	//return sigsend(pid, signo);
	return -1;
}
