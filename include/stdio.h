/*
 *    include/stdio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

typedef struct _iobuf {
	int   fd;
	int   cnt;
	int   bufsiz;
	int   flag;
	char *base;
	char *ptr;
} FILE;

#define	_IOFBF		0x000
#define	_IOREAD		0x001
#define	_IOWRITE	0x002
#define	_IONBF		0x004
#define	_IOMYBUF	0x008
#define	_IOEOF		0x010
#define	_IOERR		0x020
#define	_IOLBF		0x040
#define	_IOREADING	0x080
#define	_IOWRITING	0x100
#define	_IOAPPEND	0x200
#define _IOFIFO		0x400

/* The following definitions are also in <sys/unistd.h>.
 * They should not conflict.
 */
#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define	BUFSIZ		4096
#define	EOF		(-1)

#define	FOPEN_MAX	20

#define	FILENAME_MAX	NAME_MAX

#define	TMP_MAX		999

typedef long int	fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int myprintf(char *fmt,...);
#define printf  myprintf

#endif
