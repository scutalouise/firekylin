/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _TTY_H
#define _TTY_H

#include <sys/termios.h>
#include <firekylin/sched.h>

#define CTRL_L 	0x81
#define CTRL_R 	0x82
#define SHIFT_L 0x83
#define SHIFT_R 0x84
#define ALT_L   0x85
#define ALT_R   0x86
#define F1  	0x87
#define F2  	0x88
#define F3  	0x89
#define F4  	0x8a
#define F5  	0x8b
#define F6  	0x8c
#define F7  	0x8d
#define F8  	0x8e
#define F9  	0x8f
#define F10 	0x90
#define F11 	0x91
#define F12 	0x92
#define CAPLK 	0x93

#define C(x) (x - '@')

#define MAX_CON		7	/* max vitrual console 	*/
#define MAX_COM		2	/* max rs232		*/

#define MAX_TTY		(MAX_CON+MAX_COM)

#define TTY_BUF_SIZE 1024
struct tty_buf {
	char           buf[TTY_BUF_SIZE];
	unsigned short head;
	unsigned short tail;
	unsigned short count;
	unsigned short lines;
	struct task  * wait;
};

struct tty_struct {
	struct termios termios;
	unsigned int   pgrp;
	struct tty_buf raw;
	struct tty_buf cook;
	struct tty_buf out;
	int   (*write)(struct tty_struct *tty);
	unsigned long  parm1;
	unsigned long  parm2;
};

static inline int isfull(struct tty_buf *buf)
{
	return buf->count==TTY_BUF_SIZE;
}

static inline int isempty(struct tty_buf *buf)
{
	return buf->count == 0;
}

static inline int GETCH(struct tty_buf *buf)
{
	char retval;
	retval=buf->buf[buf->tail];
	buf->tail=(buf->tail +1)% TTY_BUF_SIZE;
	buf->count--;
	return retval;
}

static inline void PUTCH(struct tty_buf *buf,char ch)
{
	buf->buf[buf->head]=ch;
	buf->count++;
	buf->head=(buf->head +1)% TTY_BUF_SIZE;
}

extern struct tty_struct tty_table[MAX_TTY+1];
extern unsigned int fg_console;
extern void copy_to_cook(struct tty_struct *tty);

#endif
