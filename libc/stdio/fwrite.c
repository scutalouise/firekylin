/*
 *	libc/stdio/fread.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from newlibc
 */

#include "stdio_loc.h"

int fwrite(void *ptr, size_t size, int count, FILE * iop)
{
	int s;

	s = size * count;
	if (iop->_flag & _IOLBF)
		while (s > 0) {
			if (--iop->_cnt > -iop->_bufsiz
					&& *(char *) ptr != '\n')
				*iop->_ptr++ = *(char *) ptr++;
			else if (__flushbuf(*(int *) ptr++, iop) == EOF)
				break;
			s--;
		}
	else
		while (s > 0) {
			if (iop->_cnt < s) {
				if (iop->_cnt > 0) {
					memcpy(iop->_ptr, ptr, iop->_cnt);
					ptr += iop->_cnt;
					iop->_ptr += iop->_cnt;
					s -= iop->_cnt;
				}
				if (__flushbuf(*(int *) ptr++,
						iop) == EOF)
					break;
				s--;
			}
			if (iop->_cnt >= s) {
				memcpy(iop->_ptr, ptr, s);
				iop->_ptr += s;
				iop->_cnt -= s;
				return (count);
			}
		}
	return (size != 0 ? count - ((s + size - 1) / size) : 0);
}
