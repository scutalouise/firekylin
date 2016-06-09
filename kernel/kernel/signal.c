/*
 *    kernel/signal.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
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

	signal = (current->sig_signal) & (~(current->sig_mask));

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

	current->sig_signal &= ~signal;
}

int sys_sigsend(pid_t pid, int signr)
{
	struct task **p;

	for (p = task_table; p < task_table + NR_TASK; p++) {
		if ((*p)->pid == pid) {
			(*p)->sig_signal |= 1 << (signr - 1);
			if ((*p)->state == TASK_SIGWAIT) {
				(*p)->state = TASK_RUN;
				sched();
			}
			return 0;
		}
	}
	return -ERSCH;
}

int sys_sigmask(int how, sigset_t *set, sigset_t *oset)
{
	struct task *current;

	current = CURRENT_TASK();

	return current->sig_mask;
}

int sys_sigwait()
{
	(CURRENT_TASK() )->state = TASK_SIGWAIT;
	sched();
	return -EINTR;
}

int sys_sigctl(int cmd ,long arg)
{
	return 0;
}
