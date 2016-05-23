/*
 *    include/arch/portio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ARCH_PORTIO_H
#define _ARCH_PORTIO_H

#define CMOSREAD(value,index)			\
__asm__("mov $0x70,%%dx\t\n"  			\
        "out %%al,%%dx\t\n"			\
        "inc %%dx\t\n"				\
        "in  %%dx,%%al\t\n"			\
        :"=a"(value)				\
        :"a"(index)				\
        :"dx")

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
