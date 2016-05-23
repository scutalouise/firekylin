/*
 * fclose.c - flush a stream and close the file
 */

#include "stdio_loc.h"

int fclose(FILE *stream)
{
	int i, retval = 0;

	for (i=0; i<FOPEN_MAX; i++){
		if (stream == __iotab[i]) {
			__iotab[i] = 0;
			break;
		}
	}

	if (i >= FOPEN_MAX)
		return EOF;

	if (fflush(stream))
		retval = EOF;
	if (close(fileno(stream)))
		retval = EOF;
	if ( io_testflag(stream , _IOMYBUF) && stream->_buf )
		free((void *)stream->_buf);
	stream->_buf = NULL;
	if (stream != stdin && stream != stdout && stream != stderr)
		free((void *)stream);
	return retval;
}
