/*
 * rewind.c - set the file position indicator of a stream to the start
 */

#include	"stdio_loc.h"

void frewind(FILE *stream)
{
	(void) fseek(stream, 0L, SEEK_SET);
	fclearerr(stream);
}
