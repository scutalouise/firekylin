/*
 *    command/rmdir.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/syscall.h>
#include <sys/unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

__syscall1(int,rmdir,char *,filename);

int main(int argc, char **argv)
{
	if(argc<2){
		printf("Usage:rmdir dirname");
		_exit(0);
	}
	if(rmdir(argv[1])<0)
		printf("%s",strerror(errno));
}
