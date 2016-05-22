/*
 *    driver/block/ramdisk.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/lock.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/hd.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>

static unsigned long rd_start = __va(0x300000);
static unsigned long rd_sectors = 0x100000 / 512;
static sleeplock_t rd_lock;

#define lock_rd()	require_lock(&rd_lock)
#define unlock_rd()	release_lock(&rd_lock)

static void rd_read(struct buffer *buffer)
{
	char *start = (char*) rd_start + buffer->b_block * 1024;
	if (MINOR(buffer->b_dev) != 0
			|| buffer->b_block >= rd_sectors / 2)
		panic("Ramdisk Read Error : dev=%d,block=%d", buffer->b_dev,
				buffer->b_block);
	lock_rd();
	memcpy(buffer->b_data, start, 1024);
	buffer->b_flag = B_VALID;
	wake_up(&buffer->b_wait);
	unlock_rd();
}

static void rd_write(struct buffer *buffer)
{
	char *start = (char*) rd_start + buffer->b_block * 1024;
	if (MINOR(buffer->b_dev) != 0
			|| buffer->b_block >= rd_sectors / 2)
		panic("Ramdisk Write Error : dev=%d,block=%d", buffer->b_dev,
				buffer->b_block);
	lock_rd();
	memcpy(start, buffer->b_data, 1024);
	buffer->b_flag = B_VALID;
	wake_up(&buffer->b_wait);
	unlock_rd();
}

static struct blk_dev rd = { "Ramdisk", NULL, NULL, rd_read, rd_write, NULL };

void rd_init(void)
{
	memset((char*) rd_start, 0, rd_sectors * 512);
	blk_table[DEV_BLK_RAMDISK] = &rd;
}

