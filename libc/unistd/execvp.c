/*
 *	libc/dirent/execvp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int execvp(const char *file, char *argv[])
{
	return execvpe(file,argv,environ);
}
