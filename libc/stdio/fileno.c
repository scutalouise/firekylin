/*
 * fileno .c - map a stream to a file descriptor
 */

#include "stdio_loc.h"

#undef fileno

int fileno(FILE *stream)
{
	return stream->_fd;
}
