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

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include

LIBM_OBJ= sin.o   cos.o   tan.o   asin.o  acos.o  atan.o  atan2.o \
          sinh.o  cosh.o  tanh.o  asinh.o acosh.o atanh.o         \
          exp.o   pow.o   log.o   log10.o sqrt.o  hypot.o         \
          fabs.o  floor.o ceil.o  fmod.o  modf.o  ldexp.o frexp.o 

.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

libm.a: $(LIBM_OBJ)
	@echo         AR       libm
	@ar rcs   libm.a       $(LIBM_OBJ) 

install:libc.a
	@echo installing libm ...
	@-cp  libc.a  $(PREFIX)/libm.a

clean: 
	@echo cleaning libm ...
	@-rm libm.a $(LIBM_OBJ)
