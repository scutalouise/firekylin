/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>

extern void con_init(void);
extern void kbd_init(void);
extern void com_init(void);

struct tty_struct *tty_table[MAX_TTY];

void copy_to_cook(struct tty_struct *tty)
{
	char ch;
	while (!isempty(&(tty->raw))) {
		ch = GETCH(&(tty->raw));
		PUTCH(&(tty->cook), ch);
		if (tty->termios.c_lflag & ECHO) {
			PUTCH(&(tty->out), ch);
			tty->write(tty);
		}
		wake_up(&(tty->cook.wait));
	}
}

static int tty_read(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	int ch;

	if (MINOR(dev) == 0) {
		printk("read from tty0");
		return -1;
	}

	tty = tty_table[MINOR(dev)];

	irq_lock();
	while (left) {
		if (!isempty(&(tty->cook))) {
			ch = GETCH(&(tty->cook));
			*buf++ = ch;
			if (ch == '\n') {
				irq_unlock();
				return size - left + 1;
			}
			if (ch == C('D')) {
				irq_unlock();
				return size - left;
			}
			left--;
			continue;
		}
		sleep_on(&(tty->cook.wait), TASK_STATE_BLOCK);
	}
	irq_unlock();
	return size - left;
}

static int tty_write(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	char ch;

	if (MINOR(dev) == 0)
		return -1;

	tty = tty_table[MINOR(dev)];

	while (left) {
		if (!isfull(&(tty->out))) {
			ch = *buf++;
			if(ch == '\n' && (tty->termios.c_oflag & ONLCR))
				PUTCH(&(tty->out), '\r');
			PUTCH(&(tty->out), ch);
			left--;
			continue;
		}
		tty->write(tty);
	}
	tty->write(tty);
	return size - left;
}

static int tty_ioctl(dev_t dev, int cmd, long arg)
{
	return -1;
}

static struct char_device tty = { "TTY", NULL, NULL, tty_read, tty_write,
		tty_ioctl };

void tty_init(void)
{
	con_init();
	kbd_init();
	com_init();
	char_table[DEV_CHAR_TTY] = &tty;
}
