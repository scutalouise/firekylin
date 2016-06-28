/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fclose(FILE *stream)
{
	int i, retval;

	if (!stream)
		return EOF;

	for (i = 0; i < MAX_OPEN; i++) {
		if (stream == __iotab[i]) {
			__iotab[i] = 0;
			break;
		}
	}
	if (i >= MAX_OPEN)
		return EOF;

	fflush(stream);

	retval = close(stream->_fd);

	if (stream->_buf){
		free(stream->_buf);
		stream->_buf=NULL;
	}

	if (stream != stdin && stream != stdout && stream != stderr)
		free(stream);
	return retval;
}
