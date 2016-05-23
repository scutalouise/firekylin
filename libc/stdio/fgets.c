/*
 * fgets.c - get a string from a file
 */

#include "stdio_loc.h"

char * fgets(FILE *stream, char *s, size_t n)
{
	int ch;
	char *ptr;

	ptr = s;
	while (--n > 0 && (ch = __getc(stream)) != EOF) {
		*ptr++ = ch;
		if ( ch == '\n')
			break;
	}
	if (ch == EOF) {
		if (feof(stream)) {
			if (ptr == s)
				return NULL;
		} else
			return NULL;
	}
	*ptr = '\0';
	return s;
}
