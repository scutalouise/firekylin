/*
 *    include/firekylin/driver.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _DRIVER_H
#define _DRIVER_H

#include <sys/types.h>
#include <firekylin/fs.h>

#define DEV(major,minor)	(((major<<8)&0xff00) |((minor)&0xff))
#define MAJOR(dev)		(((dev)>>8)&0xff)
#define MINOR(dev)		((dev)&0xff)

#define DEV_CHAR_MAX		3
#define DEV_CHAR_MEM		1
#define DEV_CHAR_TTY		2

#define DEV_BLK_MAX		3
#define DEV_BLK_RAMDISK		1
#define DEV_BLK_FLOPPY		2
#define DEV_BLK_ATAPI		3

#define ROOT_DEV		DEV(DEV_BLK_ATAPI,1)

struct char_dev {
	char *name;
	int  (*open)(dev_t dev);
	int  (*close)(dev_t dev);
	int  (*read)(dev_t dev, char *buf, off_t off,size_t size);
	int  (*write)(dev_t dev, char *buf, off_t off,size_t size);
	int  (*ioctl)(dev_t dev, int cmd, long arg);
};

struct blk_dev {
	char *name;
	int  (*open)(dev_t dev);
	int  (*close)(dev_t dev);
	void (*read)(struct buffer *buffer);
	void (*write)(struct buffer *buffer);
	int  (*ioctl)(dev_t dev, int cmd, long arg);
};

extern struct char_dev *char_table[];
extern struct blk_dev *blk_table[];

#endif
