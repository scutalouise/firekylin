/*
 *    command/echo.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	for(int i=0;i<argc; i++){
		printf("%s ",argv[i]);
	}
	printf("\n");
}
