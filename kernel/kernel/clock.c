/*
 *    kernel/clock.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/param.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/portio.h>
#include <firekylin/timer.h>
#include <firekylin/lock.h>

#define LATCH		(1193180/HZ)

time_t start_time;
clock_t clock;

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

static void do_clock(struct trapframe *tf)
{
	struct task *current=CURRENT_TASK();

	outb(0x20, 0x20);
	clock++;

	if(tf->cs&3){
		current->utime++;
	}else
		current->stime++;

	/* do timer */
	if(timer_list && timer_list->time <=clock){
		(timer_list->func)(timer_list->data);
		timer_list=timer_list->next;
	}

	if (--current->count < 0) {
		current->count = 0;
		sched();
	}
}

void clock_init()
{
	outb(0x43, 0x36);
	outb(0x40, LATCH&&0xff);
	outb(0x40, LATCH>>8);
	set_trap_handle(0x20, &do_clock);
	outb(0x21, inb(0x21)&~1);
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

	return start_time = *p - clock / HZ;
}
