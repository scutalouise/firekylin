/*
 * feof.c - test if eof on a stream occurred
 */

#include "stdio_loc.h"

#undef feof

int feof(FILE *stream)
{
	return (stream->_flags & _IOEOF) != 0;
}
