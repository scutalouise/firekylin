/*
 *	libc/stdio/setvbuf.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

void setbuf(FILE *iop, char *buf)
{
	setvbuf(iop, buf, (buf ? _IOFBF : _IONBF), (size_t) BUFSIZ);
}
