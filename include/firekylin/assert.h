/*
 *    include/firekylin/assert.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ASSERT_H
#define _ASSERT_H

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

#ifdef 	NDEBUG
#define assert(expr)
#else
#define assert(expr)					\
if(!(expr)){						\
	printk("Assert %s failed, file %s ,line %d ",	\
		#expr,__FILE__,__LINE__) 		\
}

#endif
