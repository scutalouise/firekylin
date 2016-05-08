/*
 *	libc/stdio/ftell.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

long ftell(FILE *iop)
{
	long result;
	int adjust;

	if (io_testflag(iop, _IOREADING))
		adjust = -iop->_cnt;
	else if (io_testflag(iop, _IOWRITING) && iop->_buf
	&& !io_testflag(iop,_IONBF))
		adjust = iop->_ptr - iop->_buf;
	else
		adjust = 0;

	result = lseek(fileno(iop), (off_t) 0, SEEK_CUR);

	if (result == -1)
		return result;

	result += (long) adjust;
	return result;
}
