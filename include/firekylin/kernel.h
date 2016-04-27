/*
 *    include/firekylin/kernel.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include <sys/types.h>
#include <arch/portio.h>
#include <arch/string.h>
#include <firekylin/lock.h>

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

#endif
