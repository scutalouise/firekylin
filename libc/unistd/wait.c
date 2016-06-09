/*
 *	libc/unistd/wait.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <errno.h>

__syscall3(pid_t, wait, pid_t, pid, long*, status, int, options);
