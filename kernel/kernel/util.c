/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdarg.h>
#include <sys/types.h>
#include <firekylin/kernel.h>
#include <firekylin/lock.h>

extern unsigned fg_console;
extern int tty_write(dev_t dev,char * buf,off_t off,size_t size);

extern int vsprintf(char* buf, char* fmt, va_list ap);

static char printk_buf[512];

int printk(char* fmt, ...)
{
	va_list ap;
	int i;

	va_start(ap, fmt);
	i = vsprintf(printk_buf, fmt, ap);
	tty_write(fg_console+1, printk_buf, 0, i);
	return i;
}

void panic(char* fmt, ...)
{
	va_list ap;
	int i;

	printk("\nKernel Panic: ");
	va_start(ap, fmt);
	i = vsprintf(printk_buf, fmt, ap);
	tty_write(fg_console+1,printk_buf, 0,i);
	irq_disable();
	__asm__("hlt");
}
