/*
 *	libc/stdlib/exit.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>

typedef void (*atexit_func_t)(void);
atexit_func_t atexit_func_tab[32] = { NULL };
int atexit_func_num = 0;

void exit(int exit_code)
{
	//atexit_func_t fn;
	//printf("exit:comehere");
	//for (int i = 0; i < atexit_func_num; i++) {
	//	printf("\nexit3:comehere");
	//	fn = atexit_func_tab[i];
	//	(fn)();
	//}
	//printf("\nexit2:comehere");
	_exit(exit_code);
}
