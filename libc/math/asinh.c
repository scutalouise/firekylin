/*
 *	libc/math/asinh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double asinh(double x)
{
	return ln(x + sqrt(x*x + 1));
}
