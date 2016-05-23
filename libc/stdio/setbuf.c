/*
 * setbuf.c - control buffering of a stream
 */

#include "stdio_loc.h"

void setbuf(FILE *stream, char *buf)
{
	(void) setvbuf(stream, buf, (buf ? _IOFBF : _IONBF), (size_t) BUFSIZ);
}
