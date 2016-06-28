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

int stricmp(char *s1, char *s2)
{
	while (*s1 && *s2 && toupper(*s1)==toupper(*s2)){
		s1++;
		s2++;
	}

	return (int)(*s1-*s2);
}
