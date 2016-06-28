/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *envp[]={
		"PATH=/bin:/test",
		NULL
	};

	if(!fork()){
		if(open("/dev/tty1",O_RDWR,0)<0)
			exit(0);
		dup(0);
		dup(0);
		execve("/bin/sh",NULL,envp);
	}

	wait(0, NULL, 0);
}
