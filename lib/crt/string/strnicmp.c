/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>
#include <ctype.h>

int strnicmp(char *s1, char *s2, size_t n)
{
	while (n--) {
		if (*s1 && (toupper(*s1) == toupper(*s2))) {
			s1++;
			s2++;
		} else {
			return (*s1 - *s2);
		}
	}
	return 0;
}
