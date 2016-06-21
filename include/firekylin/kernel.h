/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include <sys/types.h>
#include <sys/param.h>

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

extern time_t start_time;
extern clock_t clock;

#define current_time()	start_time + clock / HZ;

extern void do_exit(long status);

static inline short swap_short(short data)
{
	union {
		char c[2];
		short d;
	} u;
	char t;
	u.d = data;
	t = u.c[0];
	u.c[0] = u.c[1];
	u.c[1] = t;

	return u.d;
}

static inline int swap_int(int data)
{
	union {
		char c[4];
		int d;
	} u;
	char t;
	u.d = data;
	t = u.c[0];
	u.c[0] = u.c[3];
	u.c[3] = t;
	t = u.c[1];
	u.c[1] = u.c[2];
	u.c[2] = t;
	return u.d;
}

#endif
