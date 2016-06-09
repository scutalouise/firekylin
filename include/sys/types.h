/*
 *    include/sys/types.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifndef NULL
#define NULL 		((void*)0)
#endif

typedef unsigned long 	size_t;
typedef long 		ssize_t;

typedef unsigned long 	time_t;
typedef unsigned long 	clock_t;

typedef unsigned int 	id_t;
typedef unsigned int 	uid_t;
typedef unsigned int 	gid_t;
typedef unsigned int 	pid_t;

typedef unsigned int 	dev_t;
typedef unsigned int 	ino_t;
typedef unsigned int 	mode_t;
typedef unsigned int 	nlink_t;

typedef unsigned long 	off_t;

#endif
