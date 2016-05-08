/*
 *	libc/unistd/kill.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

__syscall2(int, sigsend, pid_t, pid, int, signo);

int kill(pid_t pid, int signo)
{
	return sigsend(pid, signo);
}
