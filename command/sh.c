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
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MAX_ARG 64

char *ps1 = "[firkylin~]#";

struct cmd_struct {
	char *name;
	int (*fun)(int, char **);
};

int do_echo(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}

int do_clear(int argc, char **argv)
{
	printf("\0330;0P");
	for (int i = 0; i < 8 * 24; i++) {
		printf("          ");
	}
	printf("\0330;0P");
	return 0;
}

int do_cd(int argc, char **argv)
{
	if (argv[1]) {
		chdir(argv[1]);
	} else {
		chdir("/");
	}
	return 0;
}

int get_cmd(char *buf)
{
	int i = 0;
	char ch;
	while (1) {
		if (read(0, &ch, 1) < 0)
			return i;
		if (ch == '\n') {
			buf[i] = 0;
			return i;
		}

		if (ch == '\b' && i > 0)
			i--;
		else
			buf[i++] = ch;
	}
}

int parcmd(char *buf, char **argv)
{
	int i;
	for (i = 0; i < MAX_ARG; i++) {
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
	return i;
}

struct cmd_struct builtins[3] = { { "cd", do_cd }, { "echo", do_echo }, {
		"clear", do_clear }, };

int execcmd(int argc, char **argv)
{
	int pid;
	for (int i = 0; i < 3; i++) {
		if (strcmp(argv[0], builtins[i].name) == 0)
			return (*builtins[i].fun)(argc, argv);
	}

	pid = fork();
	if (!pid) {
		execvpe(argv[0], argv, NULL);
		printf("sh:%s\n", strerror(errno));
		_exit(0);
	}
	wait(pid, NULL, 0);
	return 0;
}

int main(void)
{
	char *argv[MAX_ARG];
	int argc;
	char buf[100];

	printf("\n\rWelcome To FireKylin 0.1 !\n\r");
	printf("More info:http://bbs.firekylin.cc\n\r");

	while (1) {

		printf("%s", ps1);
		if (get_cmd(buf)) {
			argc = parcmd(buf, argv);
			execcmd(argc, argv);
		}
	}
}
