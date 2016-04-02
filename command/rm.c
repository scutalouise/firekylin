/*
 *    command/rm.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/syscall.h>
#include <sys/unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

__syscall1(int,unlink,char *,filename);

int main(int argc, char **argv)
{
	if(argc<2){
		printf("Usage:rm name ...");
		_exit(0);
	}
	if(unlink(argv[1])<0)
		printf("%s",strerror(errno));
}
