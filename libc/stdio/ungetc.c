/*
 *	libc/stdio/ungetc.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int ungetc(int ch, FILE *iop)
{
	char *p;

	if (ch == EOF || !io_testflag(iop, _IOREADING))
		return EOF;
	if (iop->_ptr == iop->_buf) {
		if (iop->_cnt != 0)
			return EOF;
		iop->_ptr++;
	}
	iop->_cnt++;
	p = --(iop->_ptr);

	if (*p != (unsigned char) ch)
		*p = (unsigned char) ch;
	return ch;
}
