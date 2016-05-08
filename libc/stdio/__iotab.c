/*
 *	libc/stdio/_iotab.c
 *
 *	(C) 2016 ximo<ximoos@foxmail.com>. Port from minix
 */

#include "stdio_loc.h"

FILE __iotab[FOPEN_MAX] = {
	{ 0, 0, 0, _IOREAD,           NULL, NULL,  }, 	/* stdin  */
	{ 1, 0, 0, _IOWRITE,          NULL, NULL,  }, 	/* stdout */
	{ 2, 0, 0, _IOWRITE | _IONBF, NULL, NULL,  }, 	/* stderr */
};
