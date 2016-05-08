/*
 *	libc/stdio/fsetpos.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fsetpos(FILE *iop, fpos_t *pos)
{
	return fseek(iop, *pos, SEEK_SET);
}
