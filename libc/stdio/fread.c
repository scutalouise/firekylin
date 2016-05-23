/*
 * fread.c - read a number of members into an array
 */

#include "stdio_loc.h"

size_t fread(FILE *stream, void *ptr, size_t size, int count)
{
	char *cp = ptr;
	int c;
	size_t ndone = 0;
	size_t s;

	if (size)
		while (ndone < count) {
			s = size;
			do {
				if ((c = __getc(stream)) != EOF)
					*cp++ = c;
				else
					return ndone;
			} while (--s);
			ndone++;
		}
	return ndone;
}
