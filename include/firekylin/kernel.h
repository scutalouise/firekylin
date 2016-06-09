/*
 *    include/firekylin/kernel.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
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

#endif
