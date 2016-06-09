/*
 *	libc/unistd/setsid.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <errno.h>

__syscall0(pid_t,setsid);