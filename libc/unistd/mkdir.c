/*
 *	libc/unistd/mkdir.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/stat.h>

__syscall2(int, mkdir, char *,filename, mode_t, mode);

