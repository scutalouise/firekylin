/*
 *	libc/stdio/fprintf.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int fprintf(FILE *stream, char *fmt, ...)
{
	char buf[256];
	va_list ap;
	int i;

	i = strvformat(buf, 256, fmt, va_start(ap, fmt));
	fflush(stream);
	write(fileno(stream), buf, i);
	return i;
}
