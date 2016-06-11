/*
 *    include/firekylin/pci.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _PCI_H
#define _PCI_H

#define PCI_CONFIG_ADDR_PORT	0xCF8
#define PCI_CONFIG_DATA_PORT	0xCFC

/* offset in pic config space */
#define PCI_VENDOR_ID		0x00
#define PCI_DEVICE_ID		0x02
#define PCI_COMMAND		0x04
#define PCI_STATUS		0x06
#define PCI_REVISION_ID		0x08
#define PCI_PROG_IF		0x09
#define PCI_SUBCLASS		0x0a
#define PCI_CLASSCODE		0x0b
#define PCI_CACHE_LINE_SIZE	0x0c
#define PCI_LATENCY_TIMER	0x0d
#define PCI_HEADER_TYPE		0x0e
#define PCI_BIST		0x0f
#define PCI_BAR0		0x10
#define PCI_BAR1		0x14
#define PCI_BAR2		0x18
#define PCI_BAR3		0x1C
#define PCI_BAR4		0x20
#define PCI_BAR5		0x24

#define PCI_INTERRUPT_LINE	0x3C

typedef int 	pci_dev_t; 	/* pci config addr base */

struct pci_device{
	pci_dev_t	pci_dev;
	short		pci_vendor_id;
	short		pci_device_id;
};

#include <firekylin/portio.h>

static inline pci_dev_t pci_dev(char bus, char slot, char func)
{
	return (pci_dev_t) ((bus << 16) | (slot << 11) | (func << 8));
}

static inline
unsigned int pci_read_config(pci_dev_t pci_dev, char offset)
{
	outl(PCI_CONFIG_ADDR_PORT, 0x80000000 | pci_dev | (offset & 0xfc));
	return inl(PCI_CONFIG_DATA_PORT);
}

static inline
unsigned short pci_read_config_word(pci_dev_t pci_dev, char offset)
{
	union {
		unsigned int ret_i;
		unsigned short ret_s[2];
	} ret;

	ret.ret_i = pci_read_config(pci_dev, offset);

	if ((offset % 3) == 0)
		return ret.ret_s[0];
	else if ((offset % 3) == 2)
		return ret.ret_s[1];
	else
		return 0xffff;
}

static inline
unsigned char pci_read_config_byte(pci_dev_t pci_dev, char offset)
{
	union {
		unsigned int ret_i;
		unsigned char ret_c[4];
	} ret;

	ret.ret_i = pci_read_config(pci_dev, offset);

	if ((offset % 3) == 0)
		return ret.ret_c[0];
	else if ((offset % 3) == 1)
		return ret.ret_c[1];
	else if ((offset % 3) == 2)
		return ret.ret_c[2];
	else if ((offset % 3) == 3)
		return ret.ret_c[3];
	else
		return 0xff;
}

#endif
