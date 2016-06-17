/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/pci.h>
#include <firekylin/mm.h>

/*
 * ne2k_pci rquipped by bochs or qemu. other unknow.
 */
#define NE2K_VENDOR	0x10EC
#define NE2K_DEVICE	0x8029

/* register offset */
#define COMMAND		0	/* read the master command register */
#define CLDA0		1	/* read current local DMA address 0 */
#define PSTART		1
#define CLDA1		2	/* read current local DMA address 1 */
#define PSTOP		2
#define BOUNDARY	3	/* read boundary pointer	       */
#define TR_STATUS	4	/* read transmit sratus register */
#define TR_PAGE		4	/* write */
#define TR_COUNT0	5	/* collisions counter */
#define NCR		5
#define TR_COUNT1	6
#define INTR_STATUS	7	/* read interrupt status register */
#define CURRENT		7
#define REMOTE_ADDR0	8	/* read current remote dma address 0 */
#define CRDMA0		8
#define REMOTE_ADDR1	9	/* read current romete dma address 1 */
#define CRDMA1		9
#define REMOTE_BCOUNT0	10
#define REMOTE_BCOUNT1	11
#define RC_STATUS	12
#define RC_ATION	12
#define TR_ATION	13
#define FAE_TALLY	13
#define DATA_ATION	14
#define CRC_TALLY	14
#define INTR_MASK	15
#define MISS_PKT_TALLY	15

//#define PSTART		0x46
//#define PSTOP		0x80


struct pci_device *ne2k;

void ne2k_init(void)
{
	unsigned short iobase;
	if(!(ne2k=pci_find_device(NE2K_VENDOR,NE2K_DEVICE)))
		return (void)printk("ne2k not exsit on system\n");

	printk("ne2k--dev:%x\n",ne2k->dev);
	printk("ne2k--iobase:%x\n",ne2k->bar0 &~ 3);
	printk("ne2k--irq:%d\n",ne2k->interrput_line);

	iobase=ne2k->bar0 &~ 3;

	// stop mode.
	outb(iobase+COMMAND, 0x21);
	// data conf reg.
	outb(iobase+DATA_ATION,0x58);

	outb(iobase+REMOTE_BCOUNT0,0);
	outb(iobase+REMOTE_BCOUNT1,0);
	// recive conf reg.
	outb(iobase+RC_ATION,0);

}
