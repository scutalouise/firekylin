/*
 *    command/init.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *envp[]={
		"PATH=/bin",
		NULL
	};
	
	if(!fork()){
		if(open("/dev/tty1",O_RDWR,0)<0)
			exit(0);
		dup(0);
		dup(0);
		execve("/bin/sh",NULL,envp);
	}
	while (1) {	
		wait(0, NULL, 0);
	}
}
