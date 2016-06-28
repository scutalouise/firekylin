/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

FILE *fopen(char *filename, char *mode)
{
	int fd;
	FILE *f;

	f = malloc(sizeof(FILE));
	if (!f)
		return NULL;
	fd = open(filename, O_RDWR);
	if (fd < 0) {
		free(f);
		return NULL;
	}
	for (int i = 0; i < MAX_OPEN; i++) {
		if (__iotab[i])
			continue;
		__iotab[i] = f;

	}

	return NULL;
}
