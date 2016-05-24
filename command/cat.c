/*
 *    command/cat.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char buf[1024];
	FILE *fp;

	if(argc<2)
		return 0;

	fp=fopen(argv[1],"rw+");
	if(!fp){
		printf("fopen error");
		exit(0);
	}
	while((fgets(fp,buf,1024)))
	{
		fputs(stdout,buf);
	}
}
