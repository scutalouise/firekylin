/*
 *    include/firekylin/kernel.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include <sys/types.h>

#define irq_disable() 			\
    __asm__("cli");

#define irq_enable() 			\
    __asm__("sti");

/* Just should be used once in a function */
#define irq_lock()			\
    unsigned long  __flag;		\
    __asm__("pushf;popl %0;cli":"=m"(__flag))

/* Used must after irq_lock() */
#define irq_unlock()			\
    __asm__("pushl %0;popf"::"m"(__flag))

#include <arch/portio.h>
#include <arch/string.h>

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

#endif
