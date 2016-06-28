/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

void fflush(FILE *stream)
{
	if(!stream){
		for(int i=0;i<MAX_OPEN;i++){
			if(!__iotab[i])
				continue ;
			fflush(__iotab[i]);
		}
	}

	if(stream->_flag& WRITING){

	}


}
