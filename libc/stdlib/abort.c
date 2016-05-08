/*
 *	libc/stdlib/abort.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <signal.h>

void abort(void)
{
	sigsend(getpid(),SIGABRT);
}
