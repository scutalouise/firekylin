/*
 *	libc/math/ldexp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double ldexp(double x, int i)
{
	return x*pow(2,i);
}
