/*
 *    command/sh.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MAX_ARG 64

char *ps1 = "[firkylin~]#";

int get_cmd(char *buf)
{
	int size = read(0, buf, 100);
	buf[size] = 0;
	return size;
}

void parcmd(char *buf, char **argv)
{
	for (int i = 0; i < MAX_ARG; i++) {
		while (*buf == ' ')
			buf++;
		if (*buf == 0) {
			argv[i] = NULL;
			break;
		}

		argv[i] = buf;

		while (*buf && *buf != ' ')
			buf++;

		if (*buf != 0)
			*buf++ = 0;
	}
}

void execcmd(char **argv)
{
	int pid;
	if (strcmp(argv[0], "cd") == 0) {
		if(argv[1]){
			chdir(argv[1]);
		}else{
			chdir("/");
		}
		return ;
	}
	pid = fork();
	if (pid) {
		waitpid(pid, NULL, 0);
	} else {
		execve(argv[0], argv,NULL);
		printf("sh:%s\n",strerror(errno));
		_exit(0);
	}
}

int main(void)
{
	char *argv[MAX_ARG];
	char buf[100];

	printf("\n\n\rWelcome To FireKylin 0.1 !\n\n\r");
	printf("More info:http://firekylin.freekj.cn\n\n\r");

	while (1) {
		printf("%s", ps1);
		if (get_cmd(buf)) {
			parcmd(buf, argv);
			execcmd(argv);
		}
	}
}
