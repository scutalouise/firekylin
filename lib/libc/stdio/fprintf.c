/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int fprintf(FILE *stream, const char *fmt, ...)
{
	va_list ap;
	int i;
	char buf[512];

	fflush(stream);

	i=vsnprintf(buf,512,fmt,va_start(ap,fmt));
	write(fileno(stream),buf,i);

	return i;
}
