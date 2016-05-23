/*
 * fgetc - get an unsigned character and return it as an int
 */

#include "stdio_loc.h"

int fgetc(FILE *stream)
{
	return __getc(stream);
}
