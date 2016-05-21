/*
 *	libc/math/acosh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double acosh(double x)
{
	return ln(x + sqrt(x*x - 1));
}
