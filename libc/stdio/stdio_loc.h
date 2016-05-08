/*
 *	libc/stdio/stdio_loc.h
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_LOC_H
#define _STDIO_LOC_H

#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

extern FILE __iotab[FOPEN_MAX];

#define	io_testflag(p,x)	((p)->_flag & (x))

#endif
