/*
 * fwrite.c - write a number of array elements on a file
 */


#include "stdio_loc.h"

extern size_t fwrite(FILE *stream, void *ptr, size_t size, int count)
{
	unsigned char *cp = ptr;
	size_t s;
	size_t ndone = 0;

	if (size)
		while (ndone < count) {
			s = size;
			do {
				if (__putc(stream, (int) *cp) == EOF)
					return ndone;
				cp++;
			} while (--s);
			ndone++;
		}
	return ndone;
}
