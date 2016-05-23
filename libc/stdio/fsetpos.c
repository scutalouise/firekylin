/*
 * fsetpos.c - set the position in the file
 */

#include "stdio_loc.h"

int fsetpos(FILE *stream, fpos_t *pos)
{
	return fseek(stream, *pos, SEEK_SET);
}
