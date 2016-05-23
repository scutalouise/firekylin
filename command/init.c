/*
 *    command/init.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *envp[]={
		"PATH=/bin"
	};
	while (1) {
		if (!fork()) {
			open("/dev/tty1", O_RDWR, 0);
			dup(0);
			dup(0);
			execve("/bin/sh", NULL, envp);
			_exit(0);
		}
		waitpid(0, NULL, 0);
	}
}
