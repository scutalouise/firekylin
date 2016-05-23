/*
 * fclearerr.c - clear error and end-of-file indicators of a stream
 */

#include "stdio_loc.h"

#undef fclearerr

void fclearerr(FILE *stream)
{
	stream->_flags &= ~(_IOERR|_IOEOF);
}
