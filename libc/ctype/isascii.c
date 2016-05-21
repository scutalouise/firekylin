/*
 *	libc/ctype/isascii.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <ctype.h>

#undef isascii

int isascii(int c)
{
	return (c <= 0x7f);
}
