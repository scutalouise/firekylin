/*
 *	libc/math/hypot.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double hypot(double x, double y)
{
	return sqrt(x * x + y * y);
}
