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
#include <firekylin/lock.h>
#include <firekylin/pci.h>
#include <firekylin/mm.h>
#include <firekylin/string.h>
/*
 * ne2k_pci rquipped by bochs or qemu. other unknow.
 */
#define NE2K_VENDOR	0x10EC
#define NE2K_DEVICE	0x8029

/* ne2k register offset */
#define CR		0x00

/* page 0, read */
#define CLDA0		0x01
#define CLDA1		0x02
#define BNRY		0x03    /* rw */
#define TSR		0x04
#define NCR		0x05
#define FIFO		0x06
#define ISR		0x07	/* rw */
#define CRDA0		0x08
#define CRDA1		0x09
#define RSR		0x0C
#define CNTR0		0x0D
#define CNTR1		0x0E
#define CNTR2		0x0F

/* page 0 write */
#define PSTART		0x01	/* read page 2 */
#define PSTOP		0x02	/* read page 2 */
#define TPSR		0x04	/* read page 2 */
#define TBCR0		0x05
#define TBCR1		0x06
#define RSAR0		0x08
#define RSAR1		0x09
#define RBCR0		0x0A
#define RBCR1		0x0B
#define RCR		0x0C	/* read page 2 */
#define TCR		0x0D	/* read page 2 */
#define DCR		0x0E	/* read page 2 */
#define IMR		0x0F	/* read page 2 */

/* page 1 read/write */
#define PAR0		0x01
#define PAR1		0x02
#define PAR2		0x03
#define PAR3		0x04
#define PAR4		0x05
#define PAR5		0x06
#define CURR		0x07
#define MAR0		0x08
#define MAR1		0x09
#define MAR2		0x0A
#define MAR3		0x0B
#define MAR4		0x0C
#define MAR5		0x0D
#define MAR6		0x0E
#define MAR7		0x0F

#define DATA		0x10
#define RESET		0x1F

static struct pci_device *ne2k;
static unsigned short base;
static unsigned char irq;
static unsigned char mac[6];
static unsigned short rx_next=0x47;

/*
 * ne2k reg : CR, ISR, IMR, DCR, TCR, TSR, RCR, RSR.
 *            CLDA0,1 PSTART PSTOP BNRY TPSR TBCR0,1
 *            NCR FIFO CRDA0,1 RSAR0,1 RBCR0,1 CNTR0
 *            CNTR1 CNTR2 PAR0-5 CURR MAR0-7
 */

int ne2k_send(char *data, short len)
{
	while (inb(base + CR) == 0x26)
		;

	len = (len + 1) & ~1;

	outb(base + RSAR0, 0);
	outb(base + RSAR1, 0x40);

	outb(base + RBCR0, len & 0xff);
	outb(base + RBCR1, (len >> 8) & 0xff);

	outb(base + CR, 0x12); // write and start.

	/*
	 * use DMA, also need this?, really don't know.
	 */
	outs(base + DATA, data, len);

	while ((inb(base + ISR) & 0x40) == 0)
		;
	outb(base + ISR, 0x40);

	/*
	 * does need to set this evey packet, does it will change?
	 */
	outb(base + TPSR, 0x40);

	outb(base + TBCR0, len & 0xff);
	outb(base + TBCR1, (len >> 8) & 0xff);

	outb(base + CR, 0x06);

	return 0;
}

void do_ne2k(struct trapframe *tf)
{
	printk("ne2k intrrupt happen");
	outb(base+ISR,0xff);
	if (irq >= 8)
		outb(0xa0, 0x20);
	outb(0x20, 0x20);
}


char arpdata[80] =
	"\xff\xff\xff\xff\xff\xff\xb0\xc4\x20\x00\x00\x00\x08\x06\x00\x01"
	"\x08\x00\x06\x04\x00\x01\xb0\xc4\x20\x00\x00\x00\x0a\x00\x01\x15"
	"\x00\x00\x00\x00\x00\x00\x0a\x00\x01\x08\x00\x00\x00\x00\x00\x00";


void ne2k_init(void)
{
	if (!(ne2k = pci_find_device(NE2K_VENDOR, NE2K_DEVICE)))
		return (void) printk("ne2k not exsit on system\n");

	base = ne2k->bar0 & ~3;
	irq = ne2k->interrput_line;

	printk("ne2k--iobase:%x\n", base);
	printk("ne2k--irq:%d\n", irq);

	set_trap_handle(irq+0x20, do_ne2k);
	if (irq >= 8)
		outb(0xa1, inb(0xa1)&~(1<<(irq-8)));
	else
		outb(0x21, inb(0xa1)&~(1<<irq));

	outb(base + RESET, inb(base + RESET));
	while ((inb(base + ISR) & 0x80) == 0)
		;
	printk("ne2k reset done");

	outb(base + CR,  0x21);
	outb(base + DCR, 0x49);
	outb(base + TCR, 0x00);
	outb(base + RCR, 0x20);
	outb(base + IMR, 0x00);
	outb(base + ISR, 0xFF);

	outb(base + TPSR, 0x40);
	outb(base + PSTART, rx_next-1);
	outb(base + PSTOP, 0x80);
	outb(base + BNRY, rx_next-1);
	outb(base + CR, 0x61);
	outb(base + CURR, rx_next);
	outb(base + CR, 0x21);

	outb(base + RSAR0, 0);
	outb(base + RSAR1, 0);
	outb(base + RBCR0, 24);
	outb(base + RBCR1, 0);
	outb(base + CR,    0x0A);
	printk("ne2k MAC: ");
	for(int i=0;i<6;i++){
		mac[i]=inb(base+DATA);
		printk("%x:",mac[i]);
	}
	printk("\b\n");

	outb(base + CR, 0x61);
	outb(base + PAR0,mac[0]);
	outb(base + PAR1,mac[1]);
	outb(base + PAR2,mac[2]);
	outb(base + PAR3,mac[3]);
	outb(base + PAR4,mac[4]);
	outb(base + PAR5,mac[5]);

	outb(base + CR, 0x22);
	outb(base + IMR,0x1b);

	int j='A';
	//while(1){
		memset(arpdata,j,80);
		j++;
	ne2k_send(arpdata,80);

	for(int i=0;i<0xffffff;i++)
		;

	memset(arpdata,j,80);
			j++;
		ne2k_send(arpdata,80);
	//}
}
