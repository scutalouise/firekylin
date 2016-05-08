/*
 *	libc/stdio/fread.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from newlibc
 */

#include "stdio_loc.h"

int fread(void *ptr, size_t size, int count, FILE *iop)
{
	int s;
	int c;

	s = size * count;

	while (s > 0) {
		if (iop->_cnt < s) {
			if (iop->_cnt > 0) {
				memcpy(ptr, iop->_ptr, iop->_cnt);
				ptr += iop->_cnt;
				s -= iop->_cnt;
			}
			/*
			 * filbuf clobbers _cnt & _ptr,
			 * so don't waste time setting them.
			 */
			if ((c = __fillbuf(iop)) == EOF)
				break;
			*(char *) ptr++ = c;
			s--;
		}
		if (iop->_cnt >= s) {
			memcpy(ptr, iop->_ptr, s);
			iop->_ptr += s;
			iop->_cnt -= s;
			return (count);
		}
	}
	return (size != 0 ? count - ((s + size - 1) / size) : 0);
}
