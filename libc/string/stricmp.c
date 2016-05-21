/*
 *	libc/string/stricmp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
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
