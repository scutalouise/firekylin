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

extern void do_exit(long status);

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

int sys_sigact(unsigned int signr, struct sigaction *newact,
		struct sigaction *oldact)
{
	struct task *current;

	if (signr > 32 || signr == SIGKILL)
		return -EINVAL;

	current = CURRENT_TASK();

	if (oldact)
		memcpy(oldact, &(current->sigtable[signr-1]),
				sizeof(struct sigaction));
	if (newact)
		memcpy(&(current->sigtable[signr-1]), newact,
				sizeof(struct sigaction));

	return 0;
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
