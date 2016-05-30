/*
 *    command/bg.c
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
	if(argc<2)
		return ;
	if(!fork()){
		execvp(argv[1],argv+1);
	}
	exit(0);
}

