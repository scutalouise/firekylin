/*
 *	libc/stdio/fclose.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

int fclose(FILE *fp)
{
	int retval = 0;

	if (fflush(fp))
		retval = EOF;
	if (close(fileno(fp)))
		retval = EOF;
	if ( io_testflag(fp,_IOMYBUF) && fp->_buf)
		free((void *) fp->_buf);
	fp->_buf = NULL;
	return retval;
}
