/*
 *    include/firekylin/tty.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _TTY_H
#define _TTY_H

#include <sys/termios.h>
#include <firekylin/sched.h>

#define MAX_CON		7	/* max vitrual console 	*/
#define MAX_COM		2	/* max rs232		*/

#define MAX_TTY		(MAX_CON+MAX_COM)

#define TTY_BUF_SIZE 1024
struct tty_buf {
	char           buf[TTY_BUF_SIZE];
	unsigned short head;
	unsigned short tail;
	unsigned short count;
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

#define __INC(a)	((a)=((a)+1)%TTY_BUF_SIZE)

#define isfull(tty_buf)		((tty_buf).count == TTY_BUF_SIZE)
#define isempty(tty_buf)	(!((tty_buf).count))
#define PUTCH(tty_buf,ch)	\
	((tty_buf).buf[(tty_buf).head]=ch,(tty_buf).count++,__INC((tty_buf).head))
#define GETCH(tty_buf,ch)	\
	(ch=(tty_buf).buf[(tty_buf).tail],__INC((tty_buf).tail),(tty_buf).count--)

extern struct tty_struct tty_table[MAX_TTY+1];
extern unsigned int fg_console;

#endif
