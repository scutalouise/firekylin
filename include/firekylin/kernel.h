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

typedef char * va_list;

#define va_start(ap,fmt)   ap=(va_list)&fmt+sizeof(int)
#define va_arg(ap,type)	  (ap+=sizeof(int),*((type*)(ap-sizeof(int))))

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

extern time_t start_time;
extern clock_t click;

#define current_time()	start_time + click / HZ;

extern void do_exit(long status);

#include <firekylin/sched.h>

extern void sigsend(struct task *p, int signo);

#define SOFTIRQ_TIMER		0
#define SOFTIRQ_INET		1

extern void softirq_raise(unsigned int index);
extern int softirq_setaction(unsigned int index, void (*action)(long data),
		long data);

#endif
