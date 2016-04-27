/*
 *	libc/stdio/stdout.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

FILE *stdout = { 1, 0, 0, _IOWRITE, NULL, NULL };
