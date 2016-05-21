/*
 *    driver/tty.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>

extern void con_init(void);
extern void keyboard_init(void);
extern void rs_init(void);

struct tty_struct console;

struct tty_struct *getty(dev_t dev)
{
	dev = MINOR(dev);
	if (dev == 1)
		return &console;
	if (dev == 2)
		return &com1;
	panic("Not Available TTY");
	return NULL;
}

int tty_read(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	char ch;

	tty = getty(dev);
	irq_lock()
	;
	while (left) {
		if (!isempty(tty->raw)) {
			GETCH(tty->raw, ch);
			*buf++ = ch;
			if (ch == '\n') {
				irq_unlock();
				return size - left+1;
			}
		} else {
			sleep_on(&(tty->raw.wait));
			continue;
		}
		left--;
	}
	irq_unlock();
	return size - left;
}

int tty_write(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	char ch;

	tty = getty(dev);
	while (left) {
		if (!isfull(tty->out)) {
			ch = *buf++;
			PUTCH(tty->out, ch);
			left--;
			continue;
		}
		tty->write(tty);
	}
	tty->write(tty);
	return size - left;
}

int tty_ioctl(dev_t dev, int cmd, long arg)
{
	return 0;
}

struct char_dev tty = { "TTY", NULL, NULL, tty_read, tty_write, tty_ioctl };

extern int con_write(struct tty_struct *tty);

void tty_init(void)
{
	con_init();
	keyboard_init();
	rs_init();
	console.write = con_write;
	char_table[DEV_CHAR_TTYX] = &tty;
}
