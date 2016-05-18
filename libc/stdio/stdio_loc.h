/*
 *	libc/stdio/stdio_loc.h
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_LOC_H
#define _STDIO_LOC_H

#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#define	io_testflag(p,x)	((p)->_flag & (x))

#if defined(__LONG_LONG_SUPPORTED)
typedef long long printval_s_t;
typedef unsigned long long printval_u_t;
#else
typedef long printval_s_t;
typedef unsigned long printval_u_t;
#endif

#ifndef	NOFLOAT
char *_ecvt(long double value, int ndigit, int *decpt, int *sign);
char *_fcvt(long double value, int ndigit, int *decpt, int *sign);
#endif	/* NOFLOAT */

#define	FL_LJUST	0x0001		/* left-justify field */
#define	FL_SIGN		0x0002		/* sign in signed conversions */
#define	FL_SPACE	0x0004		/* space in signed conversions */
#define	FL_ALT		0x0008		/* alternate form */
#define	FL_ZEROFILL	0x0010		/* fill with zero's */
#define	FL_SHORT	0x0020		/* optional h */
#define	FL_LONG		0x0040		/* optional l */
#define	FL_LONGDOUBLE	0x0080		/* optional L */
#define	FL_WIDTHSPEC	0x0100		/* field width is specified */
#define	FL_PRECSPEC	0x0200		/* precision is specified */
#define FL_SIGNEDCONV	0x0400		/* may contain a sign */
#define	FL_NOASSIGN	0x0800		/* do not assign (in scanf) */
#define	FL_NOMORE	0x1000		/* all flags collected */
#define	FL_LONGLONG	0x2000		/* 64-bit for ints */

extern FILE __iotab[FOPEN_MAX];

extern int __doprintf(FILE *iop, char *fmt, va_list ap);
extern int __doscanf(FILE *iop, char *fmt, va_list ap);

#endif
