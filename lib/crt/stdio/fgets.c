/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

char * fgets(FILE *stream, char *buf, size_t n)
{
	char c;
	char *p = buf;

	while (n-- && (c = __getc(stream) != EOF) &&c != '\n')
		*p++ = c;

	if (feof(stream))
		return NULL;

	return (p == buf) ? NULL : buf;
}
