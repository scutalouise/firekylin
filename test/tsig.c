/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

__attribute__((__stdcall__)) int signal_handle(int signo ,int retval)
{
	printf("__signo=%d, retval=%x\n",signo,retval);
	return retval;
}

int main(int argc, char *argv[])
{

	printf("set signal handle\n");

	sigact(SIGUSR1, signal_handle);
	printf("set singal handle ok!\n");
	int j=5;
	while(j--){

		sigsend(getpid(),SIGUSR1);

		for(int i=0;i<0xfffff;i++);

		printf("have send signal\n");

	}
}
