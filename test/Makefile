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
LD=ld -m elf_i386 -T ../script/ldscript  ../lib/csu/csu.o

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../lib/crt/crt.a

OBJS=tpipe tsig test1 t_strcspn tmath t_strtod tstdio

LUA_OBJS=tlua1.lua

.s.o:
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@$(CC) $(CFLAGS) -o $@  $<

all:$(OBJS)

install: $(OBJS) $(LUA_OBJS)
	for obj in $(OBJS) ; do cp $$obj $(PREFIX)/$$obj; done
	for obj in $(LUA_OBJS) ; do cp $$obj $(PREFIX)/$$obj; done

clean:
	-rm *.o $(OBJS)

$(OBJS):%:%.o $(LIB)
	@echo CC       $<
	@$(LD) -o  $@  $<  $(LIB)
