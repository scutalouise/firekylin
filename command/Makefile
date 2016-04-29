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

OBJS=init sh ls echo cat sync mkdir touch cp ll rm ed link

command: $(OBJS)

init: init.c
	$(CC) $(CFLAGS) -o init.o init.c
	$(LD) -o init init.o  $(LIB)
sh: sh.c
	$(CC) $(CFLAGS) -o sh.o sh.c
	$(LD) -o sh sh.o  $(LIB)
echo: echo.c
	$(CC) $(CFLAGS) -o echo.o echo.c
	$(LD) -o echo echo.o  $(LIB)
cat: cat.c
	$(CC) $(CFLAGS) -o cat.o cat.c
	$(LD) -o cat cat.o  $(LIB)
sync: sync.c
	$(CC) $(CFLAGS) -o sync.o sync.c
	$(LD) -o sync sync.o  $(LIB)
mkdir:mkdir.c
	$(CC) $(CFLAGS) -o mkdir.o mkdir.c
	$(LD) -o mkdir mkdir.o  $(LIB)
touch:touch.o
	$(CC) $(CFLAGS) -o touch.o touch.c
	$(LD) -o touch touch.o  $(LIB)
cp:cp.c
	$(CC) $(CFLAGS) -o cp.o cp.c
	$(LD) -o cp cp.o  $(LIB)
ls:ls.c
	$(CC) $(CFLAGS) -o ls.o ls.c
	$(LD) -o ls ls.o  $(LIB)
ll:ll.c
	$(CC) $(CFLAGS) -o ll.o ll.c
	$(LD) -o ll ll.o  $(LIB)
rm:rm.o
	$(CC) $(CFLAGS) -o rm.o rm.c
	$(LD) -o rm rm.o  $(LIB)
ed:ed.o
	$(CC) $(CFLAGS) -o ed.o ed.c
	$(LD) -o ed ed.o  $(LIB)
link:link.c
	$(CC) $(CFLAGS) -o link.o link.c
	$(LD) -o link link.o  $(LIB)

clean:
	-rm *.o $(OBJS)