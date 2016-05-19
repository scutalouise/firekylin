/*
 *	libc/math/sinh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double sinh(double x)
{
	return (exp(x)-exp(-x))/2.0;
}
