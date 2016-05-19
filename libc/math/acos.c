/*
 *	libc/math/acos.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double acos(double x)
{
	return atan2(sqrt(1-x*x),x);
}
