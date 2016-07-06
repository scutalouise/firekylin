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
LD=ld -m elf_i386 -T ../script/ldscript  ../lib/csu/crt.o

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../lib/libc/libc.a  ../lib/libm/libm.a

OBJS=init sh ls cat sync mkdir cp rm rmdir ln vi mount umount pvi

.s.o:
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@$(CC) $(CFLAGS) -o $@  $<

all:$(OBJS)

install: $(OBJS)
	for obj in $(OBJS) ; do cp $$obj $(PREFIX)/$$obj; done

clean:
	-rm *.o $(OBJS)

$(OBJS):%:%.o $(LIB)
	@echo CC       $<
	@$(LD) -o  $@  $<  $(LIB)
