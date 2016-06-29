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

LUA_LIB_O=lua-5.1/src/lapi.o     \
          lua-5.1/src/lcode.o    \
	  lua-5.1/src/ldebug.o   \
	  lua-5.1/src/ldo.o      \
	  lua-5.1/src/ldump.o    \
	  lua-5.1/src/lfunc.o    \
	  lua-5.1/src/lgc.o      \
	  lua-5.1/src/llex.o     \
	  lua-5.1/src/lmem.o     \
	  lua-5.1/src/lobject.o  \
	  lua-5.1/src/lopcodes.o \
	  lua-5.1/src/lparser.o  \
	  lua-5.1/src/lstate.o   \
	  lua-5.1/src/lstring.o  \
	  lua-5.1/src/ltable.o   \
	  lua-5.1/src/ltm.o      \
	  lua-5.1/src/lundump.o  \
	  lua-5.1/src/lvm.o      \
	  lua-5.1/src/lzio.o     \
	  lua-5.1/src/lauxlib.o  \
	  lua-5.1/src/lbaselib.o \
	  lua-5.1/src/ldblib.o   \
	  lua-5.1/src/liolib.o   \
	  lua-5.1/src/lmathlib.o \
	  lua-5.1/src/loslib.o   \
	  lua-5.1/src/ltablib.o  \
	  lua-5.1/src/lstrlib.o  \
	  lua-5.1/src/loadlib.o  \
	  lua-5.1/src/linit.o

.s.o:
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@$(CC) $(CFLAGS) -o $@  $<

complie:liblua.a lua luac 

lua:
	$(CC) $(CFLAGS) -o lua.o  lua-5.1/src/lua.c
	$(LD) -o lua lua.o ./liblua.a ../lib/crt/crt.a

luac:
	$(CC) $(CFLAGS) -o luac.o  lua-5.1/src/luac.c
	$(LD) -o luac luac.o ./liblua.a ../lib/crt/crt.a	
	
liblua.a: $(LUA_LIB_O)
	ar rcs liblua.a $(LUA_LIB_O)

install: 
	cp lua   $(PREFIX)/lua
	cp luac  $(PREFIX)/luac
	
clean:
	-rm lua luac lua.o luac.o liblua.a $(LUA_LIB_O) 