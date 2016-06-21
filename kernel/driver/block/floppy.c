/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <arch/portio.h>
#include <arch/dma.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <arch/string.h>
#include "floppy.h"

char fd_buffer[1024]; 			/* 软盘高速缓冲区地址指针 */

#define MAX_REPLIES 7
static char  fd_reply[MAX_REPLIES]; 	/* 软驱回应缓冲区 */
#define ST0 (fd_reply[0])           	/* 软驱回应0号字节 */
#define ST1 (fd_reply[1])           	/* 软驱回应1号字节 */
#define ST2 (fd_reply[2])           	/* 软驱回应2号字节 */
#define ST3 (fd_reply[3])           	/* 软驱回应3号字节 */

static int   floppy_motor = 0; 		/* 软驱马达状态字节 */

int fd_result(void)
{
	int stat, i;
	i = 0;
	for (int count = 0; count < 0xffffff; count++) {
		stat = inb(FD_STATUS)
				& (STATUS_READY | STATUS_DIR | STATUS_BUSY);
		if (stat == STATUS_READY)
			return i;
		if (stat == (STATUS_READY | STATUS_DIR | STATUS_BUSY)) {
			if (i > 7)
				break;
			fd_reply[i++] = inb(FD_DATA);
		}
	}
	panic("Get floppy status times out !\n");
	return 0;
}

int fd_sendbyte(int value)
{
	int stat, i;

	for (i = 0; i < 0xfffff; i++) {
		stat = inb(FD_STATUS) & (STATUS_READY | STATUS_DIR);
		if (stat == STATUS_READY) {
			outb(FD_DATA,value);
			return 1;
		}
	}
	printk("Unable to send byte to FDC\n");
	return 0;
}

int fd_getbyte(void)
{
	int stat, i;

	for (i = 0; i < 0xfffff; i++) {
		stat = inb(FD_STATUS)
				& (STATUS_READY | STATUS_DIR | STATUS_BUSY);
		if (stat == STATUS_READY)
			return -1;
		if (stat == 0xD0)
			return inb(FD_DATA);
	}
	printk("Unable to get byte to FDC\n");
	return 0;
}

void fd_motorOn(void)
{
	if (!floppy_motor) {
		irq_lock();
		outb(FD_DOR,28);
		floppy_motor = 1;
		irq_unlock();
	}
	return;
}

void fd_motorOff(void)
{
	if (floppy_motor) {
		irq_lock();
		outb(FD_DOR,12);
		floppy_motor = 0;
		irq_unlock();
	}
	return;
}

void fd_setmode(void)
{
	fd_sendbyte(FD_SPECIFY);
	fd_sendbyte(0xcf);
	fd_sendbyte(0x06);
	outb(FD_DCR,0);
}

void fd_setupDMA(void)
{
	irq_lock();
	dma_disable(2);
	dma_clearFF(2);
	dma_setmode(2, DMA_MODE_READ);
	dma_setaddr(2, (unsigned long) fd_buffer);
	dma_setcount(2, 1024);
	dma_enable(2);
	irq_unlock();
}

void fd_cmd(int cmd,int block)
{
	int head,track,sector;
	head = (block % (18 * 2)) / 18;
	track = block / (18 * 2);
	sector = block % 18 + 1;

	fd_motorOn();
	fd_setupDMA();
	fd_setmode();
	fd_sendbyte(cmd);
	fd_sendbyte(head * 4 + 0);
	fd_sendbyte(track); 	/*  Cylinder  */
	fd_sendbyte(head); 	/*  Head  */
	fd_sendbyte(sector); 	/*  Sector  */
	fd_sendbyte(2); 	/*  0=128, 1=256, 2=512, 3=1024, ...  */
	fd_sendbyte(18);
	fd_sendbyte(0x1B);
	fd_sendbyte(0xff);
	return;
}

struct request{
	unsigned char busy;
	unsigned char cmd;
	unsigned char nr_sect;
	unsigned char errors;
	unsigned long start_sect;
	char          *buf;
	struct buffer *bh;
	struct task   *wait;
};

static struct request fd_req;

static inline void lock_fd()
{
	irq_lock();
	while(fd_req.busy)
		sleep_on(&fd_req.wait);
	fd_req.busy=1;
	irq_unlock();
}

static inline void unlock_fd()
{
	irq_lock();
	fd_req.busy=0;
	fd_req.busy=1;
	irq_unlock();
}

void fd_read(struct buffer *buf)
{

	lock_fd();
	fd_req.cmd=FD_READ;
	fd_req.bh=buf;
	fd_cmd(FD_READ,0);
	unlock_fd();
}

void do_fd(struct trapframe *tf)
{
	outb(0xa0, 0x20);
	outb(0x20, 0x20);

	fd_result();
	if (ST1 != 0 || ST2 != 0) {
			panic("ST0 %d ST1 %d ST2 %d\n", ST0, ST1, ST2);
	}

	memcpy(fd_req.bh->b_data, fd_buffer, 1024);

	fd_motorOff();
}

void fd_init(void)
{
}
