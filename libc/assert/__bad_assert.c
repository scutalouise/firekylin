/*
 *	libc/assert/__bad_assert.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

void __bad_assert(char *expr, char* file, int line)
{
	fprintf(stderr, "Assertion failed: %s , file %s, line %d", expr, file,
			line);
	exit(0);
}
