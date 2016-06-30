/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/param.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>

pid_t sys_getpid(void)
{
	return (CURRENT_TASK() )->pid;
}

pid_t sys_setgrp(void)
{
	struct task *current = CURRENT_TASK();
	return current->grp = current->pid;
}

pid_t sys_setsid(void)
{
	struct task *task = CURRENT_TASK();

	if ((task->sid == task->pid) || (task->uid != 0))
		return -EPERM;
	task->tty = -1;
	return task->sid = task->grp = task->pid;
}

uid_t sys_getuid(void)
{
	return (CURRENT_TASK() )->uid;
}

uid_t sys_setuid(uid_t uid)
{
	if ((CURRENT_TASK() )->uid != 0)
		return -EPERM;
	return (CURRENT_TASK() )->uid = uid;
}

gid_t sys_getgid(void)
{
	return (CURRENT_TASK() )->gid;
}

gid_t sys_setgid(gid_t gid)
{
	if ((CURRENT_TASK() )->uid != 0)
		return -EPERM;
	return (CURRENT_TASK() )->gid = gid;
}

/*
 * Note: Align to 16 Bytes
 */
int sys_sbrk(unsigned int inc)
{
	unsigned int res;
	unsigned long addr;
	struct task *current;

	current = CURRENT_TASK();
	res = current->sbrk;
	inc = (inc + 0xf) & 0xfffffff0;
	current->sbrk += inc;

	addr = (res + 0xfff) & 0xfffff000;
	for (; addr <= current->sbrk; addr += 4096) {
		map_page(addr, get_page(), current->pdtr);
	}
	return res;
}

int sys_alarm(unsigned long seconds)
{
	long old;
	struct task *current;

	current = CURRENT_TASK();
	old = current->alarm;

	current->alarm = seconds ? (click + seconds * HZ) : 0;
	if (old)
		return (old - click) / HZ;
	return 0;
}

int sys_getime(long *res)
{
	time_t i = current_time();

	if (res) {
		*res = i;
	}
	return i;
}

int sys_setime(long *p)
{
	if ((CURRENT_TASK() )->uid != 0)
		return -EPERM;

	return start_time = *p - click / HZ;
}
