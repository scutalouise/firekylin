/*
 *    driver/driver.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>

struct char_dev *char_table[DEV_CHAR_MAX + 1];
struct blk_dev  *blk_table[DEV_BLK_MAX + 1];

void char_dev_init(void)
{
	extern void tty_init(void);
	extern void mem_init(void);

	tty_init();
	mem_init();
}

void blk_dev_init(void)
{
	extern void rd_init(void);
	extern void hd_init(void);

	rd_init();
	hd_init();
}
