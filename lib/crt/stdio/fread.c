/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fread(FILE *stream, char *buf, size_t size, size_t nmemb)
{
	int tmp_len=size * nmemb;
	int done=0;
	int c;

	if(!tmp_len)
		return 0;

	while(tmp_len--){
		c=__getc(stream);
		if(c==EOF)
			break;
		*buf++=c;
		done++;
	}

	return done/nmemb;
}
