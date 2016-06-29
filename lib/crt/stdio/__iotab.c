/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

FILE __stdin =  { 0, _IOLBF, 0, 0, 0, 0 };
FILE __stdout = { 1, _IOLBF, 0, 0, 0, 0 };
FILE __stderr = { 0, _IONBF, 0, 0, 0, 0 };

FILE * __iotab[MAX_OPEN] = { &__stdin, &__stdout, &__stderr, 0 };

FILE *stdin= &__stdin;
FILE *stdout= &__stdout;
FILE *stderr=&__stdout;

