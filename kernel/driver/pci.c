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

#define MAX_PCI_DEVICE		32

int pci_device_count;

struct pci_device pci_device_table[MAX_PCI_DEVICE];

/*
 * only scan the 0 bus.
 */
void pci_init(void)
{
	char bus = 0;
	char slot;
	char func;
	pci_dev_t tmp_pci_dev;
	unsigned short vendor_id;
	unsigned short device_id;

	for (slot = 0; slot < 32; slot++) {
		for (func = 0; func < 8; func++) {
			tmp_pci_dev = pci_dev(bus, slot, func);
			vendor_id = pci_read_config_word(tmp_pci_dev, 0);
			if (vendor_id == 0xffff)
				continue;
			device_id = pci_read_config_word(tmp_pci_dev, 2);

			pci_device_table[pci_device_count].pci_dev =
					tmp_pci_dev;
			pci_device_table[pci_device_count].pci_vendor_id =
					vendor_id;
			pci_device_table[pci_device_count].pci_device_id =
					device_id;

			pci_device_count++;
			if (pci_device_count >= MAX_PCI_DEVICE) {
				printk("there are too many devices, skip\n");
				return;
			}
		}
	}
}

void dump_pci(void)
{
	for (int i = 0; i < pci_device_count; i++) {
		printk("%x  %x  %x \n",
			pci_device_table[i].pci_dev,
			pci_device_table[i].pci_vendor_id,
			pci_device_table[i].pci_device_id);
	}
}

pci_dev_t pci_find_device(unsigned short vendor, unsigned short device)
{
	for (int i = 0; i < pci_device_count; i++) {
		if ((vendor == pci_device_table[i].pci_vendor_id)
			&& (device == pci_device_table[i].pci_device_id))
			return pci_device_table[i].pci_dev;
	}
	return 0;
}
