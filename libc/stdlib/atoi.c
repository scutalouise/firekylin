/*
 *	libc/stdlib/atoi.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <string.h>

int atoi(const char *s)
{
	return (int) strtol(s, (char**) NULL, 10);
}
