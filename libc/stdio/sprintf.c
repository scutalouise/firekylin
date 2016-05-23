/*
 *	libc/stdio/sprintf.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int sprintf(char * buf, char *fmt,...)
{
	va_list ap;
	int i;

	i=strvformat(buf,256,fmt,va_start(ap,fmt));
	return i;
}
