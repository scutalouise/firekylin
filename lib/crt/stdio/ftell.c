/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int ftell(FILE *stream)
{
	int ajust, retval;

	if(!stream)
		return EOF;

	if (stream->_flag & WRITING) {
		fflush(stream);
		stream->_flag &= ~WRITING;
	}

	retval = lseek(stream->_fd, 0L, SEEK_CUR);

	if(stream->_flag& READING)
		retval-=stream->_cnt;

	return retval;
}
