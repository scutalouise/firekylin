/*
 *    include/setjmp.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SETJMP_H
#define _SETJMP_H

typedef struct{
	long ebp;
	long esp;
	long eip;
	long ebx;
	long esi;
	long edi;
}jmp_buf;

extern int  setjmp(jmp_buf env);
extern void longjmp(jmp_buf env,int val);

#endif
