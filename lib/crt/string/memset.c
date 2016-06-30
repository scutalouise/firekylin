/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

void *memset(void *s, int c, size_t n)
{
	char *t = (char*) s;

	while (n--)
		*t++ = c;
	return s;
}