/*
 *	libc/stdio/fputc.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

int fputc(int c,FILE *iop)
{
	return putc(c,iop);
}
