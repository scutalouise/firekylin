/*
 *	libc/stdio/fgetpos.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fgetpos(FILE *fp, fpos_t *pos)
{
	*pos = ftell(fp);
	if (*pos == -1)
		return -1;
	return 0;
}
