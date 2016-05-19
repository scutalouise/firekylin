/*
 *	libc/math/cosh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double cosh(double x)
{
	return (exp(x)+exp(-x))/2.0;
}
