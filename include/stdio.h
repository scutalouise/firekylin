/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/types.h>

#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

extern int    printf(char *fmt, ...);
extern int    sprintf(char *buf, char*fmt, ...);

#endif
