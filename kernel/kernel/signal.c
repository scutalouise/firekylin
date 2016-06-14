/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/signal.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/string.h>

void do_signal(struct trapframe *tf)
{
	struct task *current;
	sigset_t signal;
	int signr;

	current = CURRENT_TASK();

	signal = (current->sigarrive) & (~(current->sigarrive));

	if (!signal)
		return;

	for (signr = 0; signr < 31; signr++) {
		if (!(signal & (1 << signr)))
			continue;
		if (signr == SIGCHLD - 1)
			continue;
		else
			do_exit(signr + 1);

	}

	current->sigarrive &= ~signal;
}

int sys_sigsend(pid_t pid, int signr)
{
	struct task **p;

	for (p = task_table; p < task_table + NR_TASK; p++) {
		if ((*p)->pid == pid) {
			(*p)->sigarrive |= 1 << (signr - 1);
			if ((*p)->state == TASK_STATE_READY) {
				(*p)->state = TASK_STATE_READY;
				sched();
			}
			return 0;
		}
	}
	return -ERSCH;
}

int sys_sigwait()
{
	(CURRENT_TASK() )->state = TASK_STATE_READY;
	sched();
	return -EINTR;
}

int sys_sigctl(int cmd ,long arg)
{
	return 0;
}
