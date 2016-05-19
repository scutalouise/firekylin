/*
 *	libc/math/tanh.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <math.h>

double tanh(double x)
{
	return (exp(x)-exp(-x))/(exp(x)+exp(-x));
}
