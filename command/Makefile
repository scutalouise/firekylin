#
#    command/Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc
LD=ld -m elf_i386 -T ldscript

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../libc/libc.a

OBJS=init sh ls echo cat sync mkdir touch cp ll rm ed link t1

.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

command: $(OBJS)

init: init.o
	$(LD) -o  $@  $<  $(LIB)
sh: sh.o
	$(LD) -o  $@  $<  $(LIB)
echo: echo.o
	$(LD) -o  $@  $<  $(LIB)
cat: cat.o
	$(LD) -o  $@  $<  $(LIB)
sync: sync.o
	$(LD) -o  $@  $<  $(LIB)
mkdir:mkdir.o
	$(LD) -o  $@  $<  $(LIB)
touch:touch.o
	$(LD) -o  $@  $<  $(LIB)
cp:cp.o
	$(LD) -o  $@  $<  $(LIB)
ls:ls.o
	$(LD) -o  $@  $<  $(LIB)
ll:ll.o
	$(LD) -o  $@  $<  $(LIB)
rm:rm.o
	$(LD) -o  $@  $<  $(LIB)
ed:ed.o
	$(LD) -o  $@  $<  $(LIB)
link:link.o
	$(LD) -o  $@  $<  $(LIB)
t1:t1.o
	$(LD) -o  $@  $<  $(LIB)
		
clean:
	-rm *.o $(OBJS)