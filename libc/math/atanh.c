/*
 *	libc/math/atanh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double atan(double x)
{
	return ln((1+x)/(1-x))/2.0;
}
