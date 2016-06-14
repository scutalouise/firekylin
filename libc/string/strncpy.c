/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char *strncpy(char *dst, char *src, size_t n)
{
	char *t = dst;

	while (n-- && *src)
		*t++ = *src++;
	if(n)
		*t=0;
	return dst;
}
