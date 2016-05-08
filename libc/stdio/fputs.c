/*
 *	libc/stdio/fgets.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

int fputs(const char *s, FILE *iop)
{
	register int i = 0;

	while (*s)
		if (putc(*s++, iop) == EOF)
			return EOF;
		else
			i++;

	return i;
}
