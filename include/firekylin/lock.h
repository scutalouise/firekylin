/*
 *    include/firekylin/lock.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <sys/types.h>
#include <firekylin/sched.h>

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

#define irq_disable() 			\
    __asm__("cli");

#define irq_enable() 			\
    __asm__("sti");

/* Just should be used once in a function */
#define irq_lock()			\
    unsigned long  __flag;		\
    __asm__("pushf;popl %0;cli":"=m"(__flag))

/* Used must after irq_lock() */
#define irq_unlock()			\
    __asm__("pushl %0;popf"::"m"(__flag))

typedef struct sleeplock {
	pid_t        pid; 	/* which task hold the lock,default 0 */
	struct task *wait; 	/* task list wait for this lock       */
} sleeplock_t;

static inline void require_lock(sleeplock_t *lock)
{
	pid_t pid=(CURRENT_TASK())->pid;

	irq_lock();
	if(pid==lock->pid){
		panic("Lock has locked by %d",pid);
	}
	while(lock->pid){
		sleep_on(&(lock->wait));
	}
	lock->pid=pid;
	irq_unlock();
}

static inline void release_lock(sleeplock_t *lock)
{
	irq_lock();
	lock->pid=0;
	wake_up(&(lock->wait));
	irq_unlock();
}

#endif
