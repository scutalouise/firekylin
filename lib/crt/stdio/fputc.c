/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fputc(FILE *stream, int ch)
{
	__putc(stream, ch);
	if ((stream->_flag & 0x000f) == _IONBF) {
		fflush(stream);
		return 0;
	}
	if (((stream->_flag & 0x000f) == _IONBF) && (ch = '\n')) {
		fflush(stream);
		return 0;
	}
	return 0;
}
