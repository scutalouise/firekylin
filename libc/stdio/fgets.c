/*
 *	libc/stdio/fgets.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

char * fgets(char *s, size_t n, FILE *iop)
{
	int ch;
	char *ptr;

	ptr = s;
	while (--n > 0 && (ch = getc(iop)) != EOF) {
		*ptr++ = ch;
		if (ch == '\n')
			break;
	}
	if (ch == EOF) {
		if (feof(iop)) {
			if (ptr == s)
				return NULL;
		} else
			return NULL;
	}
	*ptr = '\0';
	return s;
}
