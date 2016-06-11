/*
 *    driver/pci.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
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
	unsigned short vendor_id;
	unsigned short device_id;

	printk("sacn pci:\n  vendor_id\t device_id\t slot\t func\n");
	for (slot = 0; slot < 32; slot++) {
		for (func = 0; func < 8; func++) {
			vendor_id = pci_read_config_word(
					pci_dev(bus, slot, func), 0);
			if (vendor_id == 0xffff)
				continue;
			device_id = pci_read_config_word(
					pci_dev(bus, slot, func), 2);
			printk("  %x\t  %x\t %x\t %x --%x\n", vendor_id,
					device_id, slot, func,
					pci_read_config(
							pci_dev(bus, slot,
									func),
							0));
		}
	}
}
