/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/lock.h>

#define NR_SOFTIRQ	16

struct softirq_action {
	void (*action)(unsigned long data);
	unsigned long data;
};

unsigned long softirq_map;
struct softirq_action softirq_actions[NR_SOFTIRQ];

struct task *softirq_wait;

void softirq_raise(unsigned int index)
{
	if(index>=NR_SOFTIRQ)
		return ;
	irq_lock();
	softirq_map|=1<<index;
	irq_unlock();
	wake_up(&softirq_wait);
}

int softirq_setaction(unsigned int index, void (*action)(unsigned long data),
		unsigned long data)
{
	if (index >NR_SOFTIRQ )
		panic("set_sofirq_action index too big %d",index);

	if(softirq_actions[index].action !=NULL)
		panic("set_softirq_action action has exsit %d",index);

	softirq_actions[index].action=action;
	softirq_actions[index].data=data;

	return 0;
}

extern int sys_fork(void);

void softirq_init(void)
{
	printk("init softirq\n");
	softirq_map = 0;
	for (int i = 0; i < NR_SOFTIRQ; i++) {
		softirq_actions[i].action = NULL;
		softirq_actions[i].data = 0;
	}
	softirq_wait = NULL;

	if(sys_fork())
		return ;

	setpriority(1);

	while (1) {

		while (!softirq_map)
			sleep_on(&softirq_wait, TASK_STATE_BLOCK);

		for (int i = 0; i < NR_SOFTIRQ; i++) {
			if (!(softirq_map & (1 << i)))
				continue;
			irq_lock();
			softirq_map &= ~(1 << i);
			irq_unlock();
			(softirq_actions[i].action)(softirq_actions[i].data);
		}
	}
}
