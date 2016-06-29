/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDLIB_H
#define _STDLIB_H

typedef struct {
	int quot;
	int rem;
} div_t;

typedef struct {
	long quot;
	long rem;
} ldiv_t;

extern char **environ;

extern int    abs(int i);
extern void * malloc(long nbytes);
extern void   free(void *p);
extern char * getenv(char *name);
extern void   exit(int exit_code);

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

#endif
