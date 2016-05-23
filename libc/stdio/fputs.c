/*
 * fputs - print a string
 */

#include "stdio_loc.h"

int fputs(FILE *stream, char *s)
{
	int i = 0;

	while (*s)
		if (__putc(stream,*s++) == EOF)
			return EOF;
		else
			i++;
	return i;
}
