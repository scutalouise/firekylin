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
#include <firekylin/timer.h>
#include <firekylin/lock.h>

static struct timer *timer_list;

void add_timer(struct timer *timer_ptr)
{
	struct timer *tmp=timer_list;

	irq_lock();
	if (!timer_list) {
		timer_list = timer_ptr;
		timer_ptr->next = NULL;
	}

	while (tmp->next && (tmp->next->time < timer_ptr->time))
		tmp = tmp->next;
	timer_ptr->next = tmp->next;
	tmp->next = timer_ptr;
	irq_unlock();
}

void del_timer(struct timer *timer_ptr)
{
	struct timer *tmp = timer_list;

	irq_lock();
	if (timer_list == timer_ptr) {
		timer_list = timer_ptr->next;
		return;
	}
	while (tmp->next && (tmp->next != timer_ptr))
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	irq_unlock();
}
