/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdio.h>

int buf[1024];

int main(int argc, char *argv[])
{
	for(int i=0;i<1024;i++)
		if(buf[i])
			printf("buf[%d]=%x\t",i,buf[i]);

}
