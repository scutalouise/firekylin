/*
 *    kernel/exit.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>

void do_exit(long exitcode)
{
	extern int sys_close(int fd);
	struct task * current=CURRENT_TASK();
	current->state = TASK_STATE_EXIT;
	current->status=exitcode;
	free_mm();
	if(current->parent->state == TASK_STATE_PAUSE){
		current->parent->state = TASK_STATE_READY;
	}

	if(current->pwd)
		iput(iunlock(current->pwd));
	for(int i=0;i<NR_OPEN;i++)
		if(current->file[i])
			sys_close(i);
	sched();
}

void sys_exit(long status)
{
	do_exit((status << 8) & 0xff00);
}
