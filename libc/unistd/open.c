/*
 *	libc/unistd/setuid.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <errno.h>

__syscall3(int, open, char*, filename, int, flag, mode_t, mode);
