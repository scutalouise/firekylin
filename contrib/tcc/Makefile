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
CFLAGS=-g -c -x c  -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include 
LIB=../../lib/libc/libc.a  ../../lib/libm/libm.a

P=$(shell echo $$HOME)
S=$(P)/tcc-0.9.26

OBJS=$(S)/tcc.o      $(S)/libtcc.o   $(S)/tccpp.o    $(S)/tccgen.o   \
     $(S)/tccelf.o   $(S)/tccasm.o   $(S)/i386-gen.o $(S)/i386-asm.o
     
.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

CFLAGS+=-DTCC_TARGET_I386 -DCONFIG_TCC_STATIC -UTCC_IS_NATIVE -I . -I $(S)
	
tcc: $(S) $(S)/config.h $(OBJS) comp.o $(LIB) 
	@echo  LD  tcc
	@$(LD) -o $@ $(OBJS) comp.o $(LIB)
		
install: 
	cp tcc    $(PREFIX)/tcc 

clean:
	@echo cleaning tcc ...
	@rm tcc  $(S)/config.h $(OBJS) comp.o 

$(S)/config.h:config.h
	@cp config.h $(S)/config.h
	
$(P)/tcc-0.9.26:$(P)/tcc-0.9.26.tar.bz2
	echo Uncompressing tcc-0.9.26.tar.bz2 ...
	cd $(P) && tar -jxf tcc-0.9.26.tar.bz2
	
$(P)/tcc-0.9.26.tar.bz2:
	echo Downloading tcc-0.9.26.tar.bz2 ...
	wget -P $(P) http://ftp.twaren.net/Unix/NonGNU//tinycc/tcc-0.9.26.tar.bz2
