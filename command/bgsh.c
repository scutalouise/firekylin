/*
 *    command/bgsh.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int pid;
	if(argc<2)
		return ;
	
	if(!(pid=fork())){
		close(0);
		close(1);
		close(2);
		if(open(argv[1],O_RDWR,0)<0){
			printf("open errer %s",argv[1]);
			exit(0);
		}
		dup(0);
		dup(0);
		execve("/bin/sh",NULL,environ);
	}
	printf("%d",pid);
	exit(0);
}

