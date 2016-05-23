/*
 *    include/arch/partion.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ARCH_PARTION_H
#define _ARCH_PARTION_H

struct partition {
	unsigned char boot_ind;
	unsigned char head;
	unsigned char sector;
	unsigned char cyl;
	unsigned char sys_ind;
	unsigned char end_head;
	unsigned char end_sector;
	unsigned char end_cyl;
	unsigned int  start_sect;
	unsigned int  nr_sects;
};

#endif
