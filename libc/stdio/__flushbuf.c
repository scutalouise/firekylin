/*
 *	libc/stdio/__flushbuf.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

static int do_write(int d, char *buf, int nbytes)
{
	int c;

	/* POSIX actually allows write() to return a positive value less
	 than nbytes, so loop ...
	 */
	while ((c = write(d, buf, nbytes)) > 0 && c < nbytes) {
		nbytes -= c;
		buf += c;
	}
	return c > 0;
}

int __flushbuf(int c, FILE * iop)
{
	if (fileno(iop) < 0)
		return (unsigned char) c;
	if (!io_testflag(iop, _IOWRITE))
		return EOF;
	if (io_testflag(iop, _IOREADING) && !feof(iop))
		return EOF;

	iop->_flag &= ~_IOREADING;
	iop->_flag |= _IOWRITING;

	if (!io_testflag(iop, _IONBF)) {
		if (!iop->_buf) {
			if (iop == stdout /*&& isatty(fileno(stdout))*/) {
				if (!(iop->_buf = (char *) malloc(BUFSIZ))) {
					iop->_flag |= _IONBF;
				} else {
					iop->_flag |= _IOLBF | _IOMYBUF;
					iop->_bufsiz = BUFSIZ;
					iop->_cnt = -1;
				}
			} else {
				if (!(iop->_buf = (char *) malloc(BUFSIZ))) {
					iop->_flag |= _IONBF;
				} else {
					iop->_flag |= _IOMYBUF;
					iop->_bufsiz = BUFSIZ;
					if (!io_testflag(iop, _IOLBF))
						iop->_cnt = BUFSIZ - 1;
					else
						iop->_cnt = -1;
				}
			}
			iop->_ptr = iop->_buf;
		}
	}

	if (io_testflag(iop, _IONBF)) {
		char c1 = c;

		iop->_cnt = 0;
		if (io_testflag(iop, _IOAPPEND)) {
			if (lseek(fileno(iop), 0L, SEEK_END) == -1) {
				iop->_flag |= _IOERR;
				return EOF;
			}
		}
		if (write(fileno(iop), &c1, 1) != 1) {
			iop->_flag |= _IOERR;
			return EOF;
		}
		return (unsigned char) c;
	} else if (io_testflag(iop, _IOLBF)) {
		*iop->_ptr++ = c;
		/* iop->_cnt has been updated in putc macro. */
		if (c == '\n' || iop->_cnt == -iop->_bufsiz) {
			int count = -iop->_cnt;

			iop->_ptr = iop->_buf;
			iop->_cnt = 0;

			if (io_testflag(iop, _IOAPPEND)) {
				if (lseek(fileno(iop), 0L, SEEK_END) == -1) {
					iop->_flag |= _IOERR;
					return EOF;
				}
			}
			if (!do_write(fileno(iop), (char *) iop->_buf, count)) {
				iop->_flag |= _IOERR;
				return EOF;
			}
		}
	} else {
		int count = iop->_ptr - iop->_buf;

		iop->_cnt = iop->_bufsiz - 1;
		iop->_ptr = iop->_buf + 1;

		if (count > 0) {
			if (io_testflag(iop, _IOAPPEND)) {
				if (lseek(fileno(iop), 0L, SEEK_END) == -1) {
					iop->_flag |= _IOERR;
					return EOF;
				}
			}
			if (!do_write(fileno(iop), (char *) iop->_buf, count)) {
				*(iop->_buf) = c;
				iop->_flag |= _IOERR;
				return EOF;
			}
		}
		*(iop->_buf) = c;
	}
	return (unsigned char) c;
}
