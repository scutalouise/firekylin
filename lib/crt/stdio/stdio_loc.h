/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE		1024

#define MAX_OPEN	NR_OPEN

extern FILE * __iotab[];

#define HAVEBUF		0x0100
#define READING		0x0200
#define WRITING		0x0400

extern int  __fillbuf(FILE *stream);
extern void __flushbuf(FILE *stream);

static inline int __getc(FILE *stream)
{
	if (stream->_cnt) {
		stream->_cnt--;
		return *stream->_ptr++;
	} else
		return __fillbuf(stream);
}

static inline int __putc(FILE *stream, char c)
{
	if (stream->_cnt) {
		stream->_cnt--;
		return *stream->_ptr++ = c;
	} else
		return __flushbuf(stream, c);
}
