/*
 *    command/ed.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd;
	int size;
	char buf[100];
	if(argc<2){
		printf("Usage:ed name ...");
	}
	if(mknod(argv[1],S_IFREG |0777,0)<0){
		printf("%s",strerror(errno));
		_exit(0);
	}
	fd=open(argv[1],O_RDWR,0);
	if(fd<0){
		printf("%s",strerror(errno));
		_exit(0);
	}
	while(fgets(stdin,buf,100)){
		size=strlen(buf);
		write(fd,buf,size);
	}
	close(fd);
}
