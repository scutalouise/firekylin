/*
 *	libc/stdio/_iobuftab.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "stdio_loc.h"

FILE *stdin  = { 0, 0, 0, _IOREAD, NULL, NULL };
FILE *stdout = { 1, 0, 0, _IOWRITE, NULL, NULL };
FILE *stderr = { 2, 0, 0, _IOREAD|_IOLBF, NULL, NULL};

FILE *_iobuftab[FOPEN_MAX] ={
	stdin,
	stdout,
	stderr,
	0
};
