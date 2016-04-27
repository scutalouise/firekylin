/*
 *	libc/stdio/_iobuftab.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

FILE *_iobuftab[FOPEN_MAX] ={
	stdin,
	stdout,
	stderr,
	0
};
