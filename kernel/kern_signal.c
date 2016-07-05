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
#include <arch/string.h>

void sigsend(struct task *p, int signo)
{
	if (!p)
		return;

	p->sigarrive |= 1 << (signo - 1);
	if (p->state == TASK_STATE_PAUSE)
		wake_up_proc(p);
}

void do_signal(unsigned long unused)
{
	struct trapframe *tf = (struct trapframe *) &unused;
	struct task * current;
	sigset_t signal;
	int signr;

	if (!(tf->cs & 3))
		return;

	current = CURRENT_TASK();

	signal = current->sigarrive & (~current->sigmask)
			& (~current->sigsuspend);
	if (!signal)
		return;

	for (signr = 0; signr < NR_SIG; signr++) {
		if (!(signal & (1 << signr)))
			continue;
		if (current->sighandle[signr] == SIG_IGN)
			continue;
		if (!current->sighandle[signr]) {
			if (signr == SIGCHLD - 1)
				continue;
			else
				do_exit(1 << signr);
		}

		unsigned long *esp = (unsigned long *) tf->esp;
		*(--esp) = tf->eax;
		*(--esp) = signr + 1;
		*(--esp) = tf->eip;
		tf->eip = (unsigned long) current->sighandle[signr];
		tf->esp = (unsigned long) esp;
		current->sigarrive &= ~(1 << signr);
		return;
	}

	current->sigarrive &= ~signal;
}

int sys_sigctl(int cmd, int param1, int param2, int param3)
{
	struct task *current = CURRENT_TASK();
	int ret;

	switch (cmd) {
	case SIGCTL_SETSUSPEND:
		ret = current->sigsuspend;
		current->sigsuspend = param1
				& ((1 << (SIGKILL - 1) | 1 << (SIGSTOP - 1)));
		return ret;

	case SIGCTL_GETSUSPEND:
		return current->sigsuspend;

	case SIGCTL_PAUSE:
		sleep_on(NULL, TASK_STATE_PAUSE);
		return -EINTR;

	default:
		return -ERROR;

	}
	return -ERROR;
}

int sys_sigsend(pid_t pid, unsigned int signo)
{
	struct task **p;

	if (signo > NR_SIG)
		return -EINVAL;

	if (pid > 0) {
		for (p = task_table; p < task_table + NR_TASK; p++) {
			if (*p && (*p)->pid == pid)
				sigsend(*p, signo);
		}
	}

	if (pid < 0) {
		pid = -pid;
		for (p = task_table; p < task_table + NR_TASK; p++) {
			if (*p && (*p)->grp == pid)
				sigsend(*p, signo);
		}
	}
	return 0;
}

int sys_sigmask(int how, sigset_t *set, sigset_t *oset)
{
	struct task *current = CURRENT_TASK();

	if (oset)
		*oset = current->sigmask;

	if (!set)
		return -ERROR;

	switch (how) {
	case SIG_BLOCK:
		current->sigmask |= *set;
		break;
	case SIG_UNBLOCK:
		current->sigmask &= ~(*set);
		break;
	case SIG_SETMASK:
		current->sigmask = *set;
		break;
	default:
		return -EINVAL;
	}
	current->sigmask &= ~(1 << (SIGKILL - 1) | 1 << (SIGSTOP - 1));

	return 0;
}

sigact_t sys_sigact(unsigned int signo, sigact_t sigact)
{
	struct task *current;
	sigact_t oact;

	if(signo >=NR_SIG)
		return (sigact_t)(-EINVAL);

	current=CURRENT_TASK();

	oact=current->sighandle[signo-1];
	current->sighandle[signo-1]=sigact;

	return oact;
}
