/*
 *	libc/unistd/unlink.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <errno.h>

__syscall1(int, unlink, char *,filename);
