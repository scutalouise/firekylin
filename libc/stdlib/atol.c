/*
 *	libc/stdlib/atol.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <string.h>

long atol(const char *s)
{
	return (long) strtol(s, (char**) NULL, 10);
}
