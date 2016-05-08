/*
 *	libc/stdio/__fillbuf.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int __fillbuf(FILE *iop)
{
	static char ch[FOPEN_MAX];

	iop->_cnt = 0;
	if (fileno(iop) < 0)
		return EOF;
	if (io_testflag(iop, (_IOEOF | _IOERR )))
		return EOF;
	if (!io_testflag(iop, _IOREAD)) {
		iop->_flag |= _IOERR;
		return EOF;
	}
	if (io_testflag(iop, _IOWRITING)) {
		iop->_flag |= _IOERR;
		return EOF;
	}

	if (!io_testflag(iop, _IOREADING))
		iop->_flag |= _IOREADING;

	if (!io_testflag(iop, _IONBF) && !iop->_buf) {
		iop->_buf = (char *) malloc(BUFSIZ);
		if (!iop->_buf) {
			iop->_flag |= _IONBF;
		} else {
			iop->_flag |= _IOMYBUF;
			iop->_bufsiz = BUFSIZ;
		}
	}

	/* flush line-buffered output when filling an input buffer */
	for (int i = 0; i < FOPEN_MAX; i++) {
		if (io_testflag(&__iotab[i], _IOLBF))
			if (io_testflag(&__iotab[i], _IOWRITING))
				(void) fflush(&__iotab[i]);
	}

	if (!iop->_buf) {
		iop->_buf = &ch[fileno(iop)];
		iop->_bufsiz = 1;
	}
	iop->_ptr = iop->_buf;
	iop->_cnt = read(iop->_fd, (char *) iop->_buf, iop->_bufsiz);

	if (iop->_cnt <= 0) {
		if (iop->_cnt == 0) {
			iop->_flag |= _IOEOF;
		} else
			iop->_flag |= _IOERR;

		return EOF;
	}
	iop->_cnt--;

	return *iop->_ptr++;
}
