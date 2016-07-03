/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>
#include <arch/portio.h>

#define COM1	0x3f8
#define COM2	0x2f8
#define COM3	0x3e8
#define COM4	0x2e8

#define DATA	0	/* Data register */
#define IER	1	/* Interrupt enable register */
#define LDLAB	0	/* Low DLAB */
#define HDLAB	1	/* High DLAB */
#define IIR	2	/* Interrupt Identy & FIFO control registers */
#define LCR	3	/* Line Control Register. bit 8 is DLAB */
#define MCR	4	/* Modem Control Register */
#define LSR	5	/* Line Status Register. */
#define MSR	6	/* Modem Status Register. */
#define SR	7	/* Scratch Register.  */

static struct tty_struct com_tty[MAX_COM];

static void init_com_control(unsigned short port)
{
	outb(port + IER  , 0x00);
	outb(port + LCR  , 0x80);
	outb(port + LDLAB, 0x30);
	outb(port + HDLAB, 0x00);
	outb(port + LCR  , 0x03);
	outb(port + IIR  , 0xC7);
	outb(port + MCR  , 0x0B);
	outb(port + IER  , 0x0D);
}

static int com_write(struct tty_struct *tty)
{
	char ch;

	while (!isempty(&(tty->out))) {
		ch = GETCH(&(com_tty[0].out));
		while((inb(0x3f8 + LSR) & 0x20)==0)
			;
		outb(0x3f8 + DATA , ch);
	}
	wake_up(&(com_tty[0].out.wait));
	return 0;
}

void do_com(struct trapframe *tf)
{
	char iir, data;

	while (1) {
		iir = inb(0x3fa);
		if (iir & 1)
			break;
		switch (iir & 0x6) {
		case 0:
			inb(0x3f8 + 6);
			break;
		case 2:
			printk("do_com iir&0x6=2");
			break;
		case 4:
			data = inb(0x3f8);
			if (!isfull(&com_tty[0].raw)) {
				PUTCH(&com_tty[0].raw, data);
				copy_to_cook(&com_tty[0]);
			}
			break;
		case 6:
			inb(0x3f8 + 5);
			break;
		}
	}
	outb(0x20, 0x20);
}

void com_init(void)
{
	init_com_control(0x3f8);
	set_trap_handle(0x24, do_com);
	outb(0x21, inb(0x21) & (~0x10));
	for (int i = 0; i < MAX_COM; i++) {
		tty_table[1+MAX_CON + i] = &com_tty[i];
		com_tty[i].write = com_write;
	}
}
