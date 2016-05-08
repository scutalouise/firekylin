/*
 *	libc/stdio/setvbuf.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int setvbuf(FILE *iop, char *buf, int mode, size_t size)
{
	int retval = 0;

	if (mode != _IOFBF && mode != _IOLBF && mode != _IONBF)
		return EOF;

	if (iop->_buf && io_testflag(iop, _IOMYBUF))
		free((void *) iop->_buf);

	iop->_flag &= ~(_IOMYBUF | _IONBF | _IOLBF);

	if (buf && size <= 0)
		retval = EOF;

	if (!buf && (mode != _IONBF)) {
		if (size <= 0 || (buf = (char *) malloc(size)) == NULL) {
			retval = EOF;
		} else {
			iop->_flag |= _IOMYBUF;
		}
	}

	iop->_buf = (char *) buf;

	iop->_cnt = 0;
	iop->_flag |= mode;
	iop->_ptr = iop->_buf;

	if (!buf) {
		iop->_bufsiz = 1;
	} else {
		iop->_bufsiz = size;
	}

	return retval;
}
