#
#    command/Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc
LD=ld -m elf_i386 -T ../script/ldscript

PREFIX=~/part1/bin

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../libc/libc.a

OBJS=init sh ls cat sync mkdir touch cp rm ln vi

.s.o:
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@$(CC) $(CFLAGS) -o $@  $<

command: $(OBJS)

install: $(OBJS)
	cp init   $(PREFIX)/init
	cp sh     $(PREFIX)/sh
	cp ls     $(PREFIX)/ls
	cp cat    $(PREFIX)/cat
	cp sync   $(PREFIX)/sync
	cp mkdir  $(PREFIX)/mkdir
	cp touch  $(PREFIX)/touch
	cp cp	  $(PREFIX)/cp
	cp rm     $(PREFIX)/rm
	cp ln     $(PREFIX)/ln
	cp vi     $(PREFIX)/vi
	
init: init.o
	$(LD) -o  $@  $<  $(LIB)
sh: sh.o
	$(LD) -o  $@  $<  $(LIB)
tsh: tsh.o
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
rm:rm.o
	$(LD) -o  $@  $<  $(LIB)
ln:ln.o
	$(LD) -o  $@  $<  $(LIB)
vi:vi.o
	$(LD) -o  $@  $<  $(LIB)

clean:
	-rm *.o $(OBJS)
