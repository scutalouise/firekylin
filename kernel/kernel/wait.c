/*
 *    kernel/wait.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <firekylin/string.h>

int sys_wait(pid_t pid, long *status,int options)
{
	int ret;
	struct task *current=CURRENT_TASK();

	while (1) {
		for (int i = 0; i < NR_TASK; i++) {
			if (!task_table[i]
				|| task_table[i]->state != TASK_EXIT
				|| task_table[i]->parent->pid!= current->pid) {
				continue;
			}
			ret = task_table[i]->pid;
			if(status){
				*status=task_table[i]->status;
			}
			put_page(__pa((long )task_table[i]));
			task_table[i]=NULL;
			return ret;
		}
		current->state=TASK_WAIT_CHLD;
		sched();
	}
	return pid;
}
