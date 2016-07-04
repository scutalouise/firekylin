/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

struct block_list {
	struct block_list *next;
	long size;
	char padding[8];
};

void * realloc(void *ptr, size_t size)
{
	void *tmp;

	tmp = malloc(size);

	if (!tmp)
		return NULL;

	if (ptr) {
		struct block_list *bp = (struct block_list *) ptr - 1;
		memcpy((char*) tmp, (char*) ptr,
				(bp->size-1) * sizeof(struct block_list));
		free(ptr);
	}
	return tmp;
}
