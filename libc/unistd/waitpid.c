/*
 *	libc/unistd/waitpid.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

__syscall3(int, waitpid, pid_t, pid, long *, status, int, options);
