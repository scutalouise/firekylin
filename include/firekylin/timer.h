/*
 *    include/firekylin/timer.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _TIMER_H
#define _TIMER_H

struct timer{
	clock_t       time;
	void        (*func)(long arg);
	long          data;
	struct timer *next;
};

extern void add_timer(struct timer *timer_ptr);
extern void del_timer(struct timer *timer_ptr);

#endif
