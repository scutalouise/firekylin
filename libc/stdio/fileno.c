/*
 *	libc/stdio/fileno.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

#undef fileno

int fileno(FILE *iop)
{
	return iop->_fd;
}
