/*
 * fopen.c - open a stream
 */

#include "stdio_loc.h"

#define	PMODE		0666

FILE * fopen(char *name, const char *mode)
{
	int i;
	int rwmode = 0;
	FILE *stream;
	struct stat st;
	int fd, flags = 0;

	for (i = 0; __iotab[i] != 0 ; i++) 
		if ( i >= FOPEN_MAX-1 )
			return (FILE *)NULL;

	switch(*mode++) {
	case 'r':
		flags |= _IOREAD | _IOREADING;	
		rwmode = O_READ;
		break;
	case 'w':
		flags |= _IOWRITE | _IOWRITING;
		rwmode = O_WRITE |O_CREAT | O_TRUNC;
		break;
	case 'a': 
		flags |= _IOWRITE | _IOWRITING | _IOAPPEND;
		rwmode = O_WRITE | O_APPEND | O_CREAT;
		break;         
	default:
		return (FILE *)NULL;
	}

	while (*mode) {
		switch(*mode++) {
		case 'b':
			continue;
		case '+':
			rwmode = O_RDWR;
			flags |= _IOREAD | _IOWRITE;
			continue;
		/* The sequence may be followed by additional characters */
		default:
			break;
		}
		break;
	}

	if ((fd = open(name, rwmode, PMODE)) < 0)
		return (FILE *)NULL;

	if ( fstat( fd, &st ) < 0 ) {
		close(fd);
		return (FILE *)NULL;
	}
	
	if ( S_ISFIFO(st.st_mode) )
		flags |= _IOFIFO;
	
	if (( stream = (FILE *) malloc(sizeof(FILE))) == NULL ) {
		close(fd);
		return (FILE *)NULL;
	}

	if ((flags & (_IOREAD | _IOWRITE))  == (_IOREAD | _IOWRITE))
		flags &= ~(_IOREADING | _IOWRITING);

	stream->_count = 0;
	stream->_fd = fd;
	stream->_flags = flags;
	stream->_buf = NULL;
	__iotab[i] = stream;
	return stream;
}
