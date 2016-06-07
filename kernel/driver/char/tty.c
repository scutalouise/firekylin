/*
 *    driver/tty.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>
#include <firekylin/kbd.h>

extern void con_init(void);
extern void kbd_init(void);
//extern void rs_init(void);

struct tty_struct tty_table[MAX_TTY+1];
extern int __echo__;
void copy_to_cook(struct tty_struct *tty)
{
	char ch;
	while(!isempty(tty->raw)){
		GETCH(tty->raw,ch);
		PUTCH(tty->cook,ch);
		if(__echo__){
			PUTCH(tty->out,ch);
			tty->write(tty);
		}
		wake_up(&(tty->cook.wait));
	}
}

int tty_read(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	int ch;

	if(MINOR(dev)==0){
		printk("read from tty0");
		return -1;
	}

	tty=tty_table+MINOR(dev);

	irq_lock();
	while (left) {
		if (!isempty(tty->cook)) {
			GETCH(tty->cook, ch);
			*buf++ = ch;
			if (ch == '\n') {
				irq_unlock();
				return size - left+1;
			}
			if (ch == C('D')) {
				irq_unlock();
				return size - left;
						}
		} else {
			sleep_on(&(tty->cook.wait));
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

	if(MINOR(dev)==0)
		return -1;
	tty=tty_table+MINOR(dev);

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
	kbd_init();
	//rs_init();
	for(int i=1;i<MAX_CON+1;i++){
		tty_table[i].write=con_write;
		tty_table[i].parm1=i-1;
	}
	//console.write = con_write;
	char_table[DEV_CHAR_TTY] = &tty;
}
