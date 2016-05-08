/*
 *	libc/stdlib/rand.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

static int __seed;

int rand(void)
{
	if(__seed==0)
		__seed++;
	__seed=__seed*123044543+12345;
	return __seed-1;
}

void srand(unsigned int seed)
{
	__seed=(int)seed;
}
