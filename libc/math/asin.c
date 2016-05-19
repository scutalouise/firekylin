/*
 *	libc/math/asin.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double asin(double x)
{
	return atan2(x,sqrt(1-x*x));
}
