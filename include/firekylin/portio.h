/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _PORTIO_H
#define _PORTIO_H

#define CMOSREAD(value,index)			\
__asm__("mov $0x70,%%dx\t\n"  			\
        "out %%al,%%dx\t\n"			\
        "inc %%dx\t\n"				\
        "in  %%dx,%%al\t\n"			\
        :"=a"(value)				\
        :"a"(index)				\
        :"dx")

static inline unsigned char inb(short port)
{
	char __res;
	__asm__("inb %%dx,%%al":"=a"(__res):"d"(port));
	return __res;
}

static inline void outb(short port, char data)
{
	__asm__("outb %%al,%%dx" : :"a"(data),"d"(port));
}

static inline short inw(short port)
{
	short __res;
	__asm__("inw %%dx,%%ax" : "=a" (__res) : "d" (port));
	return __res;
}

static inline void outw(short port, short data)
{
	__asm__("outw %%ax,%%dx" : :"a"(data),"d"(port));
}

static inline int inl(short port)
{
	int  __res;
	__asm__("inl %%dx,%%eax" : "=a" (__res) : "d" (port));
	return __res;
}

static inline void outl(short port, int data)
{
	__asm__("outl %%eax,%%dx" : :"a"(data),"d"(port));
}

static inline void ins(short port, void *buf, int size)
{
	__asm__("rep insw" :: "D"(buf),"d"(port),"c"(size>>1));
}

static inline void outs(short port, void *buf, int size)
{
	__asm__("rep outsw" :: "S"(buf),"d"(port),"c"(size>>1));
}

#endif
