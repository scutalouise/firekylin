/*
 *	libc/stdio/fopen.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

FILE * fopen(char *name, char *mode)
{
	int rwmode = 0, rwflags = 0;
	FILE *iop;
	struct stat st;
	int fd, flags = 0;

	switch (*mode++) {
		case 'r':
			flags |= _IOREAD | _IOREADING;
			rwmode = O_READ;
			break;
		case 'w':
			flags |= _IOWRITE | _IOWRITING;
			rwmode = O_WRITE;
			rwflags = O_CREAT | O_TRUNC;
			break;
		case 'a':
			flags |= _IOWRITE | _IOWRITING | _IOAPPEND;
			rwmode = O_WRITE;
			rwflags |= O_APPEND | O_CREAT;
			break;
		default:
			return (FILE *) NULL;
	}

	while (*mode) {
		switch (*mode++) {
			case 'b':
				continue;
			case '+':
				rwmode = O_RDWR;
				flags |= _IOREAD | _IOWRITE;
				continue;
			default:
				break;
		}
		break;
	}

	/* Perform a creat() when the file should be truncated or when
	 * the file is opened for writing and the open() failed.
	 */
	if ((rwflags & O_TRUNC) || (fd = open(name, rwmode)) < 0) {
		return NULL;
	}

	if (fstat(fd, &st) < 0) {
		close(fd);
		return (FILE *) NULL;
	}

	if (S_ISFIFO(st.st_mode))
		flags |= _IOFIFO;

	iop=&__iotab[fd];

	if ((flags & (_IOREAD | _IOWRITE)) == (_IOREAD | _IOWRITE))
		flags &= ~(_IOREADING | _IOWRITING);

	iop->_cnt = 0;
	iop->_fd = fd;
	iop->_flag = flags;
	iop->_buf = NULL;
	return iop;
}
