/*
 *	libc/stdio/stdio_loc.h
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_LOC_H
#define _STDIO_LOC_H

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define	io_testflag(p,x)	((p)->_flags & (x))

extern FILE *__iotab[FOPEN_MAX];

extern int __fillbuf(FILE *iop);
extern int __flushbuf(FILE * iop, int c);

#define	__getc(p)	(--(p)->_count >= 0 ? \
		          (int) (*(p)->_ptr++) : __fillbuf(p))
#define	__putc(p,c)	(--(p)->_count >= 0 ? \
			  (int) (*(p)->_ptr++ = (c)) :  __flushbuf((p),(c)))

#endif
