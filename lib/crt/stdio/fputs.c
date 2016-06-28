/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fputs(FILE *stream, char *s)
{
	int i = 0;
	int r;

	while (*s) {
		r = __putc(FILE, *s);
		i++;
		if (r == EOF)
			return 0;
	}

	if ((stream->_flag & 0x000f == _IONBF) ||
	    (stream->_flag & 0x000f == _IOLBF))
		fflush(stream);

	return i;
}
