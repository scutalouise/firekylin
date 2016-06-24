/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <firekylin/mm.h>
#include <firekylin/elf.h>
#include <arch/string.h>

static int read_char(struct file *file, char *buf, size_t size)
{
	dev_t dev = file->f_inode->i_rdev;
	int major = MAJOR(dev);
	if (major > DEV_CHAR_MAX || !char_table[major])
		panic("dev %x not exsit", dev);
	return char_table[major]->read(dev, buf, file->f_pos, size);
}

static int read_blk(struct file *file, char *buf, size_t size)
{
	struct buffer *bh;
	int chars, left, off;

	left = size;
	off = file->f_pos;

	while (left) {
		bh = bread(file->f_inode->i_rdev, off / 1024);
		if (!bh)
			return -EIO;
		chars = min(left, 1024 - off % 1024);
		memcpy((char*) buf, (char*) (bh->b_data + off % 1024), chars);
		brelse(bh);
		buf += chars;
		off += chars;
		left -= chars;
	}
	return size - left;
}

extern int read_pipe(struct file *file, char *buf, size_t size);

int sys_read(int fd, char *buf, size_t size)
{
	struct file *file;
	int res;

	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;

	if (!(file->f_mode & O_READ))
		return -EBADF;

	lock_file(file);
	lock_inode(file->f_inode);

	switch (file->f_inode->i_mode & S_IFMT) {
	case S_IFREG:
		res = file->f_inode->i_op->file_read(file, buf, size);
		break;
	case S_IFDIR:
		res = file->f_inode->i_op->file_readdir(file, buf, size);
		break;
	case S_IFCHR:
		res = read_char(file, buf, size);
		break;
	case S_IFBLK:
		res = read_blk(file, buf, size);
		break;
	case S_IFIFO:
		res = read_pipe(file, buf, size);
		break;
	default:
		res = -EIO;
	}

	if (res > 0)
		file->f_pos += res;

	unlock_inode(file->f_inode);
	unlock_file(file);

	return res;
}

long exec_load_file(struct inode *inode, struct buffer*bh)
{
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	long entry;
	long buf_page;
	struct file file;
	struct task *current = CURRENT_TASK();

	buf_page = __va(get_page());
	memcpy((char*) buf_page, bh->b_data, 1024);
	brelse(bh);

	file.f_inode = inode;

	ehdr = (Elf32_Ehdr *) buf_page;

	for (int i = 0; i < ehdr->e_phnum; i++) {
		phdr = (Elf32_Phdr *) (buf_page + ehdr->e_phoff
				+ i * ehdr->e_phentsize);
		if (!phdr->p_vaddr)
			continue;
		alloc_mm(current->pdtr, phdr->p_vaddr, phdr->p_memsz);
		file.f_pos = phdr->p_offset;
		inode->i_op->file_read(&file, (char*) phdr->p_vaddr,
				phdr->p_filesz);
		current->sbrk = phdr->p_vaddr + phdr->p_memsz;
		phdr++;
	}
	current->sbrk = (current->sbrk + 0xf) & 0xfffffff0;
	entry = ehdr->e_entry;
	put_page(__pa(buf_page));
	return entry;
}
