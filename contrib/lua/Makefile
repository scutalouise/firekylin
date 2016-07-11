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
LD=ld -m elf_i386 -T ../../script/ldscript  ../../lib/csu/crt.o

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include 
LIB=../../lib/libc/libc.a  ../../lib/libm/libm.a

P=$(shell echo $$HOME)
S=$(P)/lua-5.1/src

OBJS=$(S)/lapi.o     $(S)/lcode.o    $(S)/ldebug.o   $(S)/ldo.o      \
     $(S)/ldump.o    $(S)/lfunc.o    $(S)/lgc.o      $(S)/llex.o     \
     $(S)/lmem.o     $(S)/lobject.o  $(S)/lopcodes.o $(S)/lparser.o  \
     $(S)/lstate.o   $(S)/lstring.o  $(S)/ltable.o   $(S)/ltm.o      \
     $(S)/lundump.o  $(S)/lvm.o      $(S)/lzio.o     $(S)/lauxlib.o  \
     $(S)/lbaselib.o $(S)/ldblib.o   $(S)/liolib.o   $(S)/lmathlib.o \
     $(S)/loslib.o   $(S)/ltablib.o  $(S)/lstrlib.o  $(S)/loadlib.o  \
     $(S)/linit.o

.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

lua: $(S) $(S)/lua.o lualib.a $(LIB)
	@echo LD  lua 
	@$(LD) -o  $@ $(S)/lua.o lualib.a $(LIB)

lualib.a:$(OBJS)
	@echo  AR  OBJS
	@ar rcs lualib.a $(OBJS)

install: 
	cp lua   $(PREFIX)/lua

clean:
	@echo cleaning lua ...
	@rm lua $(S)/lua.o lualib.a $(OBJS)
	
$(P)/lua-5.1:$(P)/lua-5.1.tar.gz
	echo Uncompressing lua-5.1.tar.gz ...
	cd $(P) && tar -zxf lua-5.1.tar.gz
	
$(P)/lua-5.1.tar.gz:
	echo Downloading lua-5.1.tar.gz ...
	wget -P $(P) http://www.lua.org/ftp/lua-5.1.tar.gz 
