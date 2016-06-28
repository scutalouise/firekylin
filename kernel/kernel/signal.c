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
	struct trapframe *tf=(struct trapframe *)&unused;
	struct task * current;
	sigset_t signal;
	int signr;

	if(!(tf->cs & 3))
		return ;

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

		unsigned long *esp = (unsigned long *)tf->esp;
		*(--esp) = tf->eax;
		*(--esp) = signr + 1;
		*(--esp) = tf->eip;
		tf->eip = (unsigned long)current->sighandle[signr];
		tf->esp =(unsigned long) esp;
		current->sigarrive &= ~(1 << signr);
		return;
	}

	current->sigarrive &= ~signal;
}

int sys_sigctl(int cmd, int param1, int param2, int param3)
{
	struct task **p;
	struct task *current = CURRENT_TASK();
	int ret;
	pid_t pid;
	int signo;

	switch (cmd) {
	case SIGCTL_SETMASK:
		ret = current->sigmask;
		current->sigmask = param1
				& ((1 << (SIGKILL - 1) | 1 << (SIGSTOP - 1)));
		return ret;
	case SIGCTL_GETMASK:
		return current->sigmask;

	case SIGCTL_SETSUSPEND:
		ret = current->sigsuspend;
		current->sigsuspend = param1
				& ((1 << (SIGKILL - 1) | 1 << (SIGSTOP - 1)));
		return ret;

	case SIGCTL_GETSUSPEND:
		return current->sigsuspend;

	case SIGCTL_SETHANDLE:
		ret = (int) current->sighandle[param1 - 1];
		current->sighandle[param1 - 1] = (sigfunc_t ) param2;
		break;

	case SIGCTL_SEND:
		pid = (pid_t) param1;
		signo = param2;

		if (signo < 0 || signo > NR_SIG)
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

	case SIGCTL_PAUSE:
		sleep_on(NULL,TASK_STATE_PAUSE);
		return -EINTR;

	default:
		return -ERROR;

	}
	return -ERROR;
}
