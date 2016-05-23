/*
 * freopen.c - open a file and associate a stream with it
 */

#include "stdio_loc.h"

#define	PMODE		0666

FILE * freopen(FILE *stream, char *name, const char *mode)
{
	int i;
	struct stat st;
	int rwmode = 0;
	int fd, flags = stream->_flags & (_IONBF | _IOFBF | _IOLBF | _IOMYBUF);

	(void) fflush(stream);				/* ignore errors */
	(void) close(fileno(stream));

	/* Find the slot the stream had, if any. */
	for(i = 0; i < FOPEN_MAX; i++)
		if (stream == __iotab[i])
			break;

	/* If none, it might've been fclose()d; find a new slot for it. */
	if(i >= FOPEN_MAX) {
	        for (i = 0; __iotab[i] != 0 ; i++) {
                	if ( i >= FOPEN_MAX-1 )
                        	return (FILE *)NULL;
		}
	}

	/* If it was valid, it isn't any more until the freopen() succeeds. */
	__iotab[i] = 0;

	switch(*mode++) {
	case 'r':
		flags |= _IOREAD;	
		rwmode = O_READ;
		break;
	case 'w':
		flags |= _IOWRITE;
		rwmode = O_WRITE | O_CREAT | O_TRUNC;
		break;
	case 'a': 
		flags |= _IOWRITE | _IOAPPEND;
		rwmode = O_WRITE | O_APPEND | O_CREAT;
		break;         
	default:
		goto loser;
	}

	while (*mode) {
		switch(*mode++) {
		case 'b':
			continue;
		case '+':
			rwmode = O_RDWR;
			flags |= _IOREAD | _IOWRITE;
			continue;
		/* The sequence may be followed by aditional characters */
		default:
			break;
		}
		break;
	}

	if ((fd = open(name, rwmode, PMODE)) < 0)
		goto loser;

	if ( fstat( fd, &st ) == 0 ) {
		if ( S_ISFIFO(st.st_mode) )
			flags |= _IOFIFO;
	} else {
		goto loser;
	}
	
	stream->_count = 0;
	stream->_fd = fd;
	stream->_flags = flags;
	__iotab[i] = stream;
	return stream;

loser:
	if (stream != stdin && stream != stdout && stream != stderr)
		free((void *)stream);
	return (FILE *)NULL;	
}
