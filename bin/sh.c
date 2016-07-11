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

char *ps1 = "sh>";

struct cmd_struct {
	char *name;
	int (*fun)(int, char **);
};

int do_help(int argc, char **argv)
{
	printf("help information:\n");
	printf("\tcls       clear screen\n");
	printf("\tcd        change current working directory\n");
	printf("\techo      write arguments to standard output\n");
	printf("\thelp      print this information\n");
	printf("\tls        list directory\n");
	printf("\tcat       concatenate and print files\n");
	printf("\tcp        copy files\n");
	printf("\tmkdir     create dir\n");
	printf("\trmdir     rm empty dir\n");
	return 0;
}

int do_echo(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}

int do_cls(int argc, char **argv)
{
	printf("\033[1;1H");
	for (int i = 0; i < 8 * 24; i++) {
		printf("          ");
	}
	printf("\033[1;1H");
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
		if(ch == '\r')
			continue;

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

struct cmd_struct builtins[] = {
	{ "cd",    do_cd },
	{ "echo",  do_echo },
	{ "cls", do_cls },
	{ "help",  do_help }
};

int execcmd(int argc, char **argv)
{
	int pid;
	for (int i = 0; i < sizeof(builtins) / sizeof(struct cmd_struct); i++) {
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

	//do_cls(0,NULL);

	printf("Welcome To FireKylin 0.1 !\n");
	printf("More info:http://bbs.firekylin.cc\n");

	while (1) {

		printf("%s", ps1);
		if (get_cmd(buf)) {
			argc = parcmd(buf, argv);
			execcmd(argc, argv);
		}
	}
}
