///*
// *    command/ls.c
// *
// *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
// */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define PARAM_NONE 0
#define PARAM_A    1
#define PARAM_L    2
#define MAXROWLEN  80

int g_leave_len = MAXROWLEN;
int g_maxlen;

void my_error(const char* errstring, int line)
{
	fprintf(stderr, "line:%d %s", line, errstring);
	exit(1);
}

void display_single(char *name)
{
	int i, len;

	if (g_leave_len < g_maxlen) {
		printf("\n");
		g_leave_len = MAXROWLEN;
	}

	len = strlen(name);
	len = g_maxlen - len;

	printf("%-s", name);

	for (i = 0; i < len; i++) {
		printf(" ");
	}
	printf(" ");

	g_leave_len = g_leave_len - g_maxlen - 2;

}

void display_attribute(struct stat buf, char *name)
{
	char buf_time[32];

	if (S_ISLNK(buf.st_mode))
		printf("1");
	else if (S_ISREG(buf.st_mode))
		printf("-");
	else if (S_ISDIR(buf.st_mode))
		printf("d");
	else if (S_ISCHR(buf.st_mode))
		printf("c");
	else if (S_ISBLK(buf.st_mode))
		printf("b");
	else if (S_ISFIFO(buf.st_mode))
		printf("f");
	else if (S_ISSOCK(buf.st_mode))
		printf("s");

	if (buf.st_mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXUSR)
		printf("x");
	else
		printf("-");

	if (buf.st_mode & S_IRGRP)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXGRP)
		printf("x");
	else
		printf("-");

	if (buf.st_mode & S_IROTH)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXOTH)
		printf("x");
	else
		printf("-");

	printf("%7d", buf.st_nlink);

	printf("%6d", buf.st_size);
	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = 0;
	printf(" %s", buf_time);
}

void display(int flag, char *pathname)
{
	int i, j;
	struct stat buf;
	char name[30 + 1];

	for (i = 0, j = 0; i < strlen(pathname); i++) {
		if (pathname[i] == '/') {
			j = 0;
		} else
			name[j++] = pathname[i];
	}
	name[j] = 0;

	if (stat(pathname, &buf) == -1) {
		my_error("stat", __LINE__);
	}

	if (flag == PARAM_NONE) {
		if (name[0] != '.') {
			display_single(name);
		}
	} else if (flag == PARAM_A) {
		display_single(name);
	} else if (flag == PARAM_L) {
		if (name[0] != '.') {
			display_attribute(buf, name);
			printf(" %-s\n", name);
		}
	} else if (flag == (PARAM_A | PARAM_L)) {
		display_attribute(buf, name);
		printf(" %-s\n", name);
	}

}

void display_dir(int flag_param, const char *path)
{
	DIR* dir;
	struct dirent* dirent;
	char filenames[256][256 + 1], temp[256 + 1];
	int count = 0;                //总共有多少个文件

	if ((dir = opendir(path)) == NULL) {
		my_error("opendir", __LINE__);
	}

	//获取文件总数和最长文件名
	while ((dirent = readdir(dir)) != NULL) {
		if (g_maxlen < strlen(dirent->d_name))
			g_maxlen = strlen(dirent->d_name);
		count++;
	}
	closedir(dir);

	if (count > 256)
		my_error("too more file", __LINE__);

	int i, j, len = strlen(path);
	//获取目录下所有的文件名
	dir = opendir(path);
	for (i = 0; i < count; i++) {
		dirent = readdir(dir);
		if (dirent == NULL) {
			my_error("readdir", __LINE__);
		}
		strncpy(filenames[i], path, len);
		filenames[i][len] = 0;
		strcat(filenames[i], dirent->d_name);
		filenames[i][len + strlen(dirent->d_name)] = 0;
	}

	//对文件名进行排序
	for (i = 0; i < count - 1; i++)
		for (j = i + 1; j < count - 1; j++) {
			if (strcmp(filenames[i], filenames[j]) > 0) {
				strcpy(temp, filenames[j]);
				strcpy(filenames[j], filenames[i]);
				strcpy(filenames[i], temp);
			}
		}

	for (i = 0; i < count; i++)
		display(flag_param, filenames[i]);
	closedir(dir);

	//没有-l的话打印一个换行符
	if ((flag_param & PARAM_L) == 0)
		printf("\n");
}

int main(int argc, char **argv)
{
	int i, j, k;
	int num;                //记录-的个数
	char path[356 + 1];
	char param[32]; // 保存命令行参数
	int flag_param = PARAM_NONE;
	struct stat buf;

	j = 0;
	num = 0;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			for (k = 1; k < strlen(argv[i]); k++) {
				param[j] = argv[i][k];
				j++;
			}
			num++;
		}
	}

	//现在只支持-a和-l参数
	for (i = 0; i < j; i++) {
		if (param[i] == 'a') {
			flag_param |= PARAM_A;
		} else if (param[i] == 'l') {
			flag_param |= PARAM_L;
		} else {
			printf("worg arg：%c\n", param[i]);
			exit(1);
		}
	}

	param[j] = 0;

	//如果没有输入文件名或者目录，就显示当前目录
	if ((num + 1) == argc) {
		strcpy(path, "./");
		path[2] = 0;
		display_dir(flag_param, path);
		return 0;
	}

	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			strcpy(path, argv[i]);
			if (stat(path, &buf) == -1)
				my_error("stat", __LINE__);
			if (S_ISDIR(buf.st_mode)) {
				//判断目录是否以/结尾
				if (path[strlen(argv[i]) - 1] != '/') {
					path[strlen(argv[i])] = '/';
					path[strlen(argv[i] + 1)] = 0;
				} else
					path[strlen(argv[i])] = 0;

				display_dir(flag_param, path);
			} else {
				display(flag_param, path);
			}
		}
	}

	return 0;
}
