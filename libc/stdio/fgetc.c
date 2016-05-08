/*
 *	libc/stdio/fgetc.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fgetc(FILE *iop)
{
	return getc(iop);
}
