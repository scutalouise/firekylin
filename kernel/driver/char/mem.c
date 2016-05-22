/*
 *    driver/char/mem.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/mm.h>
#include <errno.h>

#define MEM_RAM		0
#define MEM_PORT	1
#define MEM_KMEM	2
#define MEM_NULL	3
#define MEM_FULL	4

#define MEM_READ	1
#define MEM_WRITE	2

static int mem_ram(int rw, char *buf, off_t off, size_t size)
{
	char *tmp = (char*) __va(off);
	if (rw == MEM_READ)
		memcpy(buf, tmp, size);
	else
		memcpy(tmp, buf, size);
	return size;
}

static int mem_port(int rw, char *buf, off_t off, size_t size)
{
	int left = size;
	while (left-- && off < 0xffff) {
		if (rw == MEM_READ)
			*buf++ = inb(off++);
		else
			outb(off++, *buf++);
	}
	return size - left;
}

static int mem_kmem(int rw, char *buf, off_t off, size_t size)
{
	char *tmp = (char*) (off);
	if (rw == MEM_READ)
		memcpy(buf, tmp, size);
	else
		memcpy(tmp, buf, size);
	return size;
}

static int mem_null(int rw, char *buf, off_t off, size_t size)
{
	if (rw == MEM_READ)
		return 0;
	else
		return size;
}

static int mem_full(int rw, char *buf, off_t off, size_t size)
{
	if (rw == MEM_READ) {
		memset(buf, 0, size);
		return size;
	} else
		return -ENOSPACE;
}

int mem_read(dev_t dev, char * buf, off_t off, size_t size)
{
	switch (MINOR(dev)) {
		case MEM_RAM:
			return mem_ram(MEM_READ, buf, off, size);
		case MEM_PORT:
			return mem_port(MEM_READ, buf, off, size);
		case MEM_KMEM:
			return mem_kmem(MEM_READ, buf, off, size);
		case MEM_NULL:
			return mem_null(MEM_READ, buf, off, size);
		case MEM_FULL:
			return mem_full(MEM_READ, buf, off, size);
		default:
			return -EIO;
	}
}

int mem_write(dev_t dev, char * buf, off_t off, size_t size)
{
	switch (MINOR(dev)) {
		case MEM_RAM:
			return mem_ram(MEM_WRITE, buf, off, size);
		case MEM_PORT:
			return mem_port(MEM_WRITE, buf, off, size);
		case MEM_KMEM:
			return mem_kmem(MEM_WRITE, buf, off, size);
		case MEM_NULL:
			return mem_null(MEM_WRITE, buf, off, size);
		case MEM_FULL:
			return mem_full(MEM_WRITE, buf, off, size);
		default:
			return -EIO;
	}
}

static struct char_dev mem = { "mem", NULL, NULL, mem_read, mem_write, NULL };

void mem_init(void)
{
	char_table[DEV_CHAR_MEM] = &mem;
}
