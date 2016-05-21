/*
 *	libc/string/strnicmp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
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
