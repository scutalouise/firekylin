/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_SYSCALL_H
#define _SYS_SYSCALL_H

#define __NR_fork		0
#define __NR_exec		1
#define __NR_sbrk		2
#define __NR_wait		3
#define __NR_exit		4
#define __NR_trace		5
#define __NR_alarm		6
#define __NR_sigctl		7
#define __NR_getpid		8
#define __NR_setgrp		9
#define __NR_setsid		10
#define __NR_getuid		11
#define __NR_setuid		12
#define __NR_getgid		13
#define __NR_setgid		14
#define __NR_access		15
#define __NR_open		16
#define __NR_read		17
#define __NR_write		18
#define __NR_close		19
#define __NR_lseek		20
#define __NR_fcntl		21
#define __NR_ioctl		22
#define __NR_pipe		23
#define __NR_mknod		24
#define __NR_mkdir		25
#define __NR_link		26
#define __NR_rename		27
#define __NR_unlink		28
#define __NR_rmdir		29
#define __NR_chdir		30
#define __NR_mount		31
#define __NR_umount		32
#define __NR_stat		33
#define __NR_fstat		34
#define __NR_chmod		35
#define __NR_chown		36
#define __NR_utime		37
#define __NR_sync		38
#define __NR_getime		39
#define __NR_setime		40
#define __NR_sigsend		41
#define __NR_sigmask		42
#define __NR_sigact		43
#define __NR_times		44

#define __syscall0(type,name) 			\
type name(void)					\
{						\
	long res;				\
	__asm__("int $0x30"			\
	    :"=a"(res)				\
	    :"a"(__NR_##name));			\
	if(res<0){				\
		errno=-res;			\
		return (type)(-1);		\
	}					\
	return (type)res;			\
}

#define __syscall1(type,name,typeb,argb) 	\
type name(typeb argb)				\
{						\
	long res;				\
	__asm__("int $0x30"			\
	    :"=a"(res)				\
	    :"a"(__NR_##name),"b"(argb));	\
	if(res<0){				\
		errno=-res;			\
		return (type)(-1);		\
	}					\
	return (type)res;			\
}

#define __syscall2(type,name,typeb,argb,typec,argc) 	\
type name(typeb argb,typec argc)			\
{							\
	long res;					\
	__asm__("int $0x30"				\
	    :"=a"(res)					\
	    :"a"(__NR_##name),"b"(argb),"c"(argc));	\
	if(res<0){					\
		errno=-res;				\
		return (type)(-1);			\
	}						\
	return (type)res;				\
}

#define __syscall3(type,name,typeb,argb,typec,argc,typed,argd) 	\
type name(typeb argb,typec argc,typed argd)			\
{								\
	long res;						\
	__asm__("int $0x30"					\
	    :"=a"(res)						\
	    :"a"(__NR_##name),"b"(argb),"c"(argc),"d"(argd));	\
	if(res<0){						\
		errno=-res;					\
		return (type)(-1);				\
	}							\
	return (type)res;					\
}

#define __syscall4(type,name,typeb,argb,typec,argc,typed,argd,typee,arge) \
type name(typeb argb,typec argc,typed argd,typee arge)			  \
{								          \
	long res;						          \
	__asm__("int $0x30"					          \
	    :"=a"(res)						          \
	    :"a"(__NR_##name),"b"(argb),"c"(argc),"d"(argd),"D"(arge));	  \
	if(res<0){						          \
		errno=-res;					          \
		return (type)(-1);				          \
	}							          \
	return (type)res;					          \
}

#endif
