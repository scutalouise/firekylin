/*
 *    include/sys/dirent.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

#define MAX_NAME_LEN	255
struct dirent{
	ino_t  d_ino;
	size_t d_reclen;
	char   d_name[MAX_NAME_LEN+1];
};

typedef struct {
	int    dd_fd;
} DIR;

DIR           *opendir(char *filename);
struct dirent *readdir(DIR *dir);
void 	       rewinddir(DIR *dir);
int 	       closedir(DIR *dir);

#endif
