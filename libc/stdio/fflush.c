/*
 *	libc/stdio/fflush.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fflush(FILE *iop)
{
	int count, c1, retval = 0;

	if (!iop) {
		for (int i = 0; i < FOPEN_MAX; i++)
			if (__iotab[i] && fflush(__iotab[i]))
				retval = EOF;
		return retval;
	}

	if (!iop->_buf || (!io_testflag(iop, _IOREADING)
			&& !io_testflag(iop, _IOWRITING)))
		return 0;
	if (io_testflag(iop, _IOREADING)) {
		/* (void) fseek(iop, 0L, SEEK_CUR); */
		int adjust = 0;
		if (io_testflag(iop, _IOFIFO)) {
			/* Can't seek in a pipe. */
			return 0;
		}
		if (iop->_buf && !io_testflag(iop, _IONBF))
			adjust = -iop->_cnt;
		iop->_cnt = 0;
		if (lseek(fileno(iop), (off_t) adjust, SEEK_CUR) == -1
				&& errno != ESPIPE) {
			iop->_flag |= _IOERR;
			return EOF;
		}
		errno = 0;
		if (io_testflag(iop, _IOWRITE))
			iop->_flag &= ~(_IOREADING | _IOWRITING);
		iop->_ptr = iop->_buf;
		return 0;
	} else if (io_testflag(iop, _IONBF))
		return 0;

	if (io_testflag(iop, _IOREAD)) /* "a" or "+" mode */
		iop->_flag &= ~_IOWRITING;

	count = iop->_ptr - iop->_buf;
	iop->_ptr = iop->_buf;

	if (count <= 0)
		return 0;

	if (io_testflag(iop, _IOAPPEND)) {
		if (_lseek(fileno(iop), 0L, SEEK_END) == -1) {
			iop->_flag |= _IOERR;
			return EOF;
		}
	}
	c1 = _write(iop->_fd, (char *) iop->_buf, count);

	iop->_cnt = 0;

	if (count == c1)
		return 0;

	iop->_flag |= _IOERR;
	return EOF;
}
