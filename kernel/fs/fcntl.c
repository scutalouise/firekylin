/*
 *    fs/fcntl.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <errno.h>

static int dupfd(int fd, unsigned int arg)
{
	extern int sys_close(int fd);
	struct task *current;

	if (arg > NR_OPEN)
		return -EBADF;

	if (arg)
		sys_close(arg);
	current = CURRENT_TASK();
	while (arg < NR_OPEN) {
		if (current->file[arg]) {
			arg++;
			continue;
		}
		current->file[arg] = current->file[fd];
		current->file[fd]->f_count++;
		return arg;
	}
	return -EMFILE;
}

int sys_lseek(int fd, long off, int where)
{
	struct file *file;
	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
			return -EBADF;
	switch (where) {
		case SEEK_SET:
			if (off < 0)
				return -EINVAL;
			file->f_pos = off;
			break;
		case SEEK_CUR:
			if (file->f_pos + off < 0)
				return -EINVAL;
			file->f_pos += off;
			break;
		case SEEK_END:
			if (file->f_inode->i_size + off < 0)
				return -EINVAL;
			file->f_pos = file->f_inode->i_size + off;
			break;
		default:
			return -EINVAL;
	}
	return file->f_pos;
}

int sys_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg)
{
	struct file *file;

	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;

	switch (cmd) {
		case F_DUPFD:
			return dupfd(fd, arg);
		default:
			return -EIO;
	}
}
