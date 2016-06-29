/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/types.h>
#include <sys/param.h>

#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define EOF		(-1)

typedef struct __iobuf {
	int    _fd;
	int    _flag;
	int    _cnt;
	int    _bufsize;
	char * _buf;
	char * _ptr;
} FILE;

#define BUFSIZ		1024
#define L_tmpnam	512

#define _IONBF		0x0001
#define _IOLBF		0x0002
#define _IOFBF		0x0003
#define _IOERR		0x0010
#define _IOEOF		0x0020

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

extern int printf(char *fmt, ...);
extern int sprintf(char *buf, char*fmt, ...);

static inline int fileno(FILE *stream)
{
	return stream->_fd;
}

static inline int feof(FILE *stream)
{
	return stream->_flag & _IOEOF;
}

static inline int ferror(FILE *stream)
{
	return stream->_flag & (_IOERR | _IOEOF);
}

static inline int fclrerr(FILE *stream)
{
	return stream->_flag &= ~(_IOERR | _IOEOF);
}

#define getc(stream)	fgetc(stream)
#define putc(stream,c)	fputc(stream,c)

#endif
