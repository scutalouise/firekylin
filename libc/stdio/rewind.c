/*
 *	libc/stdio/ungetc.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

void rewind(FILE *iop)
{
	fseek(iop, 0L, SEEK_SET);
	clearerr(iop);
}
