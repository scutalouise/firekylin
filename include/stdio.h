/*
 *    include/stdio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_H
#define _STDIO_H

typedef struct{

}FILE;
int myprintf(char *fmt,...);
#define printf  myprintf

#define NULL ((void*)0)
#define stderr 2

#endif
