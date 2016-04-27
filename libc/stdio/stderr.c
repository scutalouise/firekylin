/*
 *	libc/stdio/stderr.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

FILE * stderr = {2, 0, 0, _IOREAD|_IOLBF, NULL, NULL};
