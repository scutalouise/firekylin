/*
 * fputc.c - print an unsigned character
 */

#include "stdio_loc.h"

int fputc(FILE *stream, int c)
{
	return __putc(stream, c);
}
