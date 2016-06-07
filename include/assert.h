/*
 *    include/assert.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef	NDEBUG
#define assert(expr)
#else

#define assert(expr) 							\
    if(!(expr)){							\
	fprintf(stderr, "Assertion failed: %s , file %s, line %d", 	\
			#expr, __FILE__, __LINE__ );			\
	abort();							\
    }

#endif
