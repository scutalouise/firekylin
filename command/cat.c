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

char buf[1024];

int main(int argc, char *argv[])
{
	int fd,size;
	if(argc<2)
		return 0;

	fd=open(argv[1],O_RDWR);
	if(fd <0){
		printf("fopen error");
		exit(0);
	}
	while((size=read(fd,buf,1024)))
	{
		write(STDOUT_FILENO,buf,size);
	}
}
