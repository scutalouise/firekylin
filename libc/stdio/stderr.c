/*
 *	libc/stdio/stderr.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

FILE * stderr=&__iotab[2];
