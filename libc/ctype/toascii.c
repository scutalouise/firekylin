/*
 *	libc/ctype/toascii.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <ctype.h>

#undef toascii

int toascii(int c)
{
	return (c & 0x7f);
}
