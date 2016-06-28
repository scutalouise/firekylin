/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if(argc<2){
		printf("Usage:rm name ...");
		_exit(0);
	}
	if(unlink(argv[1])<0)
		printf("%s",strerror(errno));
}
