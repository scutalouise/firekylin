/*
 *    include/assert.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef	NDEBUG
#define assert(expr)
#else
extern void __bad_assert(char *expr, char* file, int line);

#define assert(expr) 						\
	if(!(expr)){						\
		__bad_assert(#expr,__FILE__,__LINE__); 	\
	}

#endif
