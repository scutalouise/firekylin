/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>
#include <sys/param.h>
#include <sys/signal.h>

struct tss_struct {
	unsigned long link;
	unsigned long esp0;
	unsigned long ss0;
	unsigned long esp1;
	unsigned long ss1;
	unsigned long esp2;
	unsigned long ss2;
	unsigned long cr3;
	unsigned long eip;
	unsigned long eflags;
	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;
	unsigned long esp;
	unsigned long ebp;
	unsigned long esi;
	unsigned long edi;
	unsigned long es;
	unsigned long cs;
	unsigned long ss;
	unsigned long ds;
	unsigned long fs;
	unsigned long gs;
	unsigned long ldt;
	unsigned short trap;
	unsigned short iobase;
};

struct task {
	long          kesp; 		/* kernel stack_end. 	*/
	pid_t         pid; 		/* process id.  	*/
	pid_t         grp; 		/* process group id. 	*/
	pid_t         sid; 		/* session id.  	*/
	uid_t         uid; 		/* user id. 		*/
	gid_t         gid; 		/* user group id. 	*/
	clock_t       start;		/* start time. 		*/
	clock_t       stime; 		/* system time. 	*/
	clock_t       utime; 		/* user   time. 	*/
	clock_t       cstime; 		/* child system time. 	*/
	clock_t       cutime; 		/* child user   time. 	*/
	clock_t       alarm; 		/* alarm. 		*/
	long          state; 		/* process state. 	*/
	long          count; 		/* have not used time. 	*/
	long          priority; 	/* process priority.	*/
	long          pdtr; 		/* cr3 			*/
	long          sbrk; 		/* heap end. 		*/
	long          stack; 		/* stack end. 		*/
	long 	      status; 		/* exit status. 	*/
	sigset_t      sigarrive;	/* sig arrived map 	*/
	sigset_t      sigmask;		/* sig mask    map	*/
	sigset_t      sigsuspend;	/* sig suspend map	*/
	sigfunc_t     sighandle[NR_SIG];/* sig handle table	*/
	unsigned int  tty; 		/* control tty. 	*/
	struct inode *pwd; 		/* current dir inode. 	*/
	struct file  *file[NR_OPEN]; 	/* file open point. 	*/
	struct task  *parent;		/* point to father task */
	struct task  *next;		/* point to list next   */
};

/* Values of task->state */
#define TASK_STATE_UNUSE	0	/* unused or creating.	*/
#define TASK_STATE_READY	1	/* ready  or running.	*/
#define TASK_STATE_BLOCK	2	/* wait some resource.	*/
#define TASK_STATE_PAUSE	3	/* wait singal.		*/
#define TASK_STATE_STOP		4	/* stop by singal etc.	*/
#define TASK_STATE_EXIT		5	/* task exit.		*/

#define CURRENT_TASK() 			\
    (struct task*)({ 			\
	unsigned long __res; 		\
	__asm__ __volatile__(		\
            "movl %%esp,%%eax;"		\
            "andl $0xfffff000,%%eax"	\
            :"=a"(__res)); 		\
	__res; 				\
    })

#define __switch_to(n)			\
    ({	__asm__ __volatile__ (		\
	"pushl $__ret_switch;"		\
	"pushf;"			\
	"pushl %%eax;"			\
	"pushl %%ebx;"			\
	"pushl %%ecx;"			\
	"pushl %%edx;"			\
	"pushl %%edi;"			\
	"pushl %%esi;"			\
	"pushl %%ebp;"			\
	"subl  $108,%%esp;"		\
	"fnsave (%%esp);"		\
	"movl  %%esp,%%eax;"		\
	"andl  $0xfffff000,%%eax;"	\
	"movl  %%esp,(%%eax);"		\
	"movl  %%ecx,%%esp;"		\
	"frstor (%%esp);"		\
	"addl  $108,%%esp;"		\
	"popl  %%ebp;"			\
	"popl  %%esi;"			\
	"popl  %%edi;"			\
	"popl  %%edx;"			\
	"popl  %%ecx;"			\
	"popl  %%ebx;"			\
	"popl  %%eax;"			\
	"popf;"				\
	"ret;"				\
	"__ret_switch:  ;"		\
	::"c"(task_table[n]->kesp));	\
    })

extern struct task * task_table[];

void sched(void);
void sleep_on(struct task **p);
void wake_up(struct task **p);

#endif
