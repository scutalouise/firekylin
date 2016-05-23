/*
 *	libc/unistd/execvp.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>

int execvpe(const char * file, char ** argv, char ** envp)
{
	char * path, * tmp;
	int len;
	struct stat st;
	char tmp_path[PATH_MAX];

	if ( *file=='/' || !(path=getenv("PATH")))
		return execve(file,argv,envp);

	while (*path) {
		tmp=tmp_path;
		len=0;
		while (len<PATH_MAX && *path && *path!=':') {
			*(tmp++) = *(path++);
			len++;
		}
		if (*path==':')
			path++;
		if (!len || tmp[-1]!='/') {
			*(tmp++) = '/';
			len++;
		}
		if (len>=PATH_MAX)
			continue;
		strncpy(tmp,file,PATH_MAX-len);

		if (stat(tmp_path,&st))
			continue;
		else
			if (!(st.st_mode & S_IFREG))
				continue;
		//if (!access(tmp_path,1))
		return execve(tmp_path,argv,envp);
	}
	errno = ENOENT;
	return -1;
}
