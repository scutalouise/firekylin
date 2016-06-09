/*
 *	libc/stdlib/atexit.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */


typedef void (*atexit_func_t)(void);

extern atexit_func_t atexit_func_tab[];
extern int atexit_func_num;

int atexit(void (*func)(void))
{
	if(atexit_func_num<32){
		atexit_func_tab[atexit_func_num++]=func;
		return 1;
	}
	return 0;
}
