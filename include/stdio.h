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

typedef struct __iobuf{
	int    _fd;
	int    _flag;
	int    _cnt;
	int    _bufsize;
	char * _buf;
	char * _ptr;
}FILE;

#define MAX_OPEN	NR_FILE

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

extern int    printf(char *fmt, ...);
extern int    sprintf(char *buf, char*fmt, ...);

#endif
