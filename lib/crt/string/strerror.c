/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

static char *err_str[]={
	"1.unknown error",
	"2.generic error",
	"3.operation not permitted",
	"4.no such file or directory",
	"5.interrupted function call",
	"6.input/output error",
	"7.arg list too long",
	"8.is a directory",
	"9.invalid argument",
	"10.permission denied",
	"11.bad file descriptor",
	"12.not a directory",
	"13.not enough space",
	"14.resource temporarily unavailable",
	"15.exec format error",
	"16.no such device",
	"17.too many open files",
	"18.",
	"19.",
	"20.",
	"21.",
	"22.",
	"23.",
	"24.",
	"25.",
};

char *strerror(int errno)
{
	printf("--dbg:errno:%d\n",errno);
	if(errno<0 || errno>24){
		return err_str[0];
	}
	return err_str[errno];
}
