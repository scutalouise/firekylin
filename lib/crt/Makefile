#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

AS=nasm
CC=gcc

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include

include ctype/sub.mk
include dirent/sub.mk
include math/sub.mk
include setjmp/sub.mk
include stdio/sub.mk
include stdlib/sub.mk
include string/sub.mk
include time/sub.mk
include unistd/sub.mk
     
.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

crt.a: $(LIBC_OBJ)
	@echo         AR       OBJS
	@ar rcs    crt.a     $(LIBC_OBJ) 

install:libc.a
	cp  crt.a  $(PREFIX)/crt.a

clean: 
	@echo libcrt cleaning...
	@-rm crt.a $(LIBC_OBJ)
