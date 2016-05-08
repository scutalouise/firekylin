/*
 *	libc/dirent/execlp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int execlp(const char * file, char * arg0, ...)
{
	return execvep(file,&arg0,environ);
}
