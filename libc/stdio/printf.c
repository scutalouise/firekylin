/*
 *	libc/stdio/printf.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/unistd.h>

int printf(char *fmt,...)
{
	char buf[256];
	va_list ap;
	int i;

	i=strvformat(buf,256,fmt,va_start(ap,fmt));
	fflush(stdout);
	write(fileno(stdout),buf,i);
	return i;
}
