/*
 *    include/signal.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/types.h>
#include <sys/signal.h>

/* bits of sa_flags */
#define SA_ONSTACK	0x0001	/* deliver signal on alternate stack       */
#define SA_RESETHAND	0x0002	/* reset signal handler when signal caught */
#define SA_NODEFER	0x0004	/* don't block signal while catching it    */
#define SA_RESTART	0x0008	/* automatic system call restart           */
#define SA_SIGINFO	0x0010	/* extended signal handling                */
#define SA_NOCLDWAIT	0x0020	/* don't create zombies                    */
#define SA_NOCLDSTOP	0x0040	/* don't receive SIGCHLD when child stops  */

/* values used by sigprocmask(). */
#define SIG_BLOCK          0	/* for blocking signals        */
#define SIG_UNBLOCK        1	/* for unblocking signals      */
#define SIG_SETMASK        2	/* for setting the signal mask */
#define SIG_INQUIRE        4	/* for internal use only       */

typedef void (*sig_func_t)(int);

sig_func_t signal(int signr,sig_func_t fun);

int sigaddset(sigset_t *set,int signo);
int sigdelset(sigset_t *set,int signo);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigismember(sigset_t *set,int signo);
int sigprocmask(int how,sigset_t *set ,sigset_t *oldset);
int sigaction(int sig,struct sigaction *newact,struct sigaction * oldact);
int sigsend(pid_t pid,int signo);

#endif
