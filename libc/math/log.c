/*
 *	libc/math/log.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double log(double a, double b)
{
	return ln(b)/ln(a);
}
