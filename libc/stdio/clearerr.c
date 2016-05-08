/*
 *	libc/stdio/clearerr.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

#undef clearerr

void clearerr(FILE *fp)
{
	fp->_flag &= ~(_IOERR|_IOEOF);
}
