/*
 *	libc/stdio/fseek.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fseek(FILE *iop, off_t offset, int whence)
{
	int adjust = 0;
	long pos;

	iop->_flag &= ~(_IOEOF | _IOERR);

	if (io_testflag(iop, _IOREADING)) {
		if (whence == SEEK_CUR && iop->_buf && !io_testflag(iop, _IONBF))
			adjust = iop->_cnt;
		iop->_cnt = 0;
	}

	if (io_testflag(iop, _IOWRITING)) {
		fflush(iop);
	}

	pos = lseek(fileno(iop), offset - adjust, whence);

	if (io_testflag(iop, _IOREAD) && io_testflag(iop, _IOWRITE))
		iop->_flag &= ~(_IOREADING | _IOWRITING);

	iop->_ptr = iop->_buf;
	return ((pos == -1) ? -1 : 0);
}
