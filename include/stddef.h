/*
 *    include/stddef.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#include <sys/types.h>

#ifndef __PTRDIFF_T
#define __PTRDIFF_T
typedef long prtdiff_t;
#endif

#ifndef __WCHAR_T
#define __WCHAR_T
typedef short wchar_t;
#endif

#define offestof(type,member) ((size_t)&((type*)0->member))

#endif
