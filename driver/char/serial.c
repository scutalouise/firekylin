/*
 *    driver/serial.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>

struct tty_struct com1;

void init_rs_contrl(unsigned short port)
{
	outb(port+3,0x80);
	outb(port,0x30);
	outb(port+1,0);
	outb(port+3,0x03);
	outb(port+4,0x0b);
	outb(port+1,0x0d);
	inb(port);
}

int rs_write(struct tty_struct *tty)
{
	irq_lock();
	if(!isempty(tty->out)){
		outb(0x3f8+1,inb(0x3f8+1)|0x2);
	}
	irq_unlock();
	return 0;
}

void do_rs(struct trapframe *tf)
{
	char iir,data;

	while(1){
		iir=inb(0x3fa);
		if(iir&1)
			break;
		switch(iir&0x6){
			case 0:
				inb(0x3f8+6);
				break;
			case 2:
				if(!isempty(com1.out)){
					GETCH(com1.out,data);
					outb(0x3f8,data);
					break;
				}
				outb(inb(0x3f8+1),inb(0x3f8+1)& ~0x2);
				break;
			case 4:
				data=inb(0x3f8);
				printk("%c",data);
				if(!isfull(com1.raw)){
					PUTCH(com1.raw,data);
					wake_up(&(com1.raw.wait));
				}
				PUTCH(com1.out,data);
				rs_write(&com1);
				break;
			case 6:
				inb(0x3f8+5);
				break;
		}
	}
	outb(0x20,0x20);
}

void rs_init(void)
{
	init_rs_contrl(0x3f8);
	set_trap_handle(0x24,do_rs);
	outb(0x21,inb(0x21)&(~0x10));
	com1.write=rs_write;
}
