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

#define RTL8139_VENDOR	0x10EC
#define RTL8139_DEVICE	0x8139

/* Regidters  offset form iobase*/
#define RTL8139_MAC0_5	0x00	/* 6 bytes */
#define RTL8139_MAR0_7	0x08	/* 8 bytes */
#define RTL8139_RBSTART	0x30	/* 4 bytes */
#define RTL8139_CMD	0x37	/* 1 bytes */
#define RTL8139_IMR	0x3C	/* 2 bytes */
#define RTL8139_ISR	0x3E	/* 2 bytes */

static pci_dev_t rtl8139;
static unsigned long iobase;
static unsigned char rx_buffer[8192+16];

void rtl8139_init(void)
{
	if(!(rtl8139=pci_find_device(RTL8139_VENDOR,RTL8139_DEVICE))){
		printk("rtl8139 not exist in system\n");
		return ;
	}

	printk("find rtl8139 at pci:%x\n", rtl8139);

	/* enable PCI bus Mastering*/
	unsigned short command;
	command=pci_read_config_word(rtl8139,PCI_COMMAND);
	command|=2;
	printk("rtl8139 command %x\n",command);
	pci_write_config_word(rtl8139,PCI_COMMAND,command);

	/* get iobase */
	iobase=pci_read_config(rtl8139,PCI_BAR0);
	printk("iobase %x\n",iobase);
	iobase &=0xfc;

	/* turning on the rtl8139 */
	outb(iobase+0x52,0x00);

	/* software reset */
	int count=0xcfff;
	do{
		outb(iobase+0x37,0x10);
		count--;
	}while(count && (inb(iobase+0x37)&0x10));

	printk("soft reset ready");

	/* init receive buffer */
	outl(iobase+0x30,__pa(rx_buffer));

	/* set IMR + ISR */
	outw(iobase + 0x3C ,0x0005);

	/* configuring receive buffer */
	outl(iobase + 0x44 ,0xf | (1<<7) );

	/* enable receive and transmitter */
	outb(iobase +0x37,0x0C);
}
