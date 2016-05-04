/*
 *    include/arch/portio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 *
 */

#ifndef _ARCH_PORTIO_H
#define _ARCH_PORTIO_H

static inline char inb(short port)
{
	char __res;
	__asm__("in %%dx,%%al":"=a"(__res):"d"(port));
	return __res;
}

static inline void outb(short port, char data)
{
	__asm__("out %%al,%%dx" : :"a"(data),"d"(port));
}

static inline void ins(short port, char *buf, int size)
{
	__asm__("rep insw" :: "D"(buf),"d"(port),"c"(size>>1));
}

static inline void outs(short port, char *buf, int size)
{
	__asm__("rep outsw" :: "S"(buf),"d"(port),"c"(size>>1));
}

#endif
