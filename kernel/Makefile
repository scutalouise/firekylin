#
#    kenrel/Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include

OBJS=init/head.o init/main.o  \
     kernel/entry.o kernel/trap.o   kernel/util.o  \
     kernel/sched.o kernel/signal.o kernel/clock.o \
     kernel/fork.o  kernel/exit.o   kernel/exec.o  \
     driver/char/console.o driver/char/keyboard.o driver/char/serial.o \
     driver/char/tty.o driver/block/hd.o driver/driver.o \
     mm/memory.o \
     fs/buffer.o fs/super.o fs/inode.o fs/read.o fs/stat.o fs/open.o \
     fs/write.o fs/fcntl.o fs/create.o fs/pipe.o fs/ioctl.o fs/close.o \
     fs/minix/super.o fs/minix/inode.o fs/minix/bitmap.o \
     fs/minix/namei.o fs/minix/file.o fs/minix/operation.o 
       
.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@ $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@ $<
	
kernel.bin: $(OBJS)
	@echo         LD      OBJS
	@ld -m elf_i386 -e _start -Ttext 0xC0010000 --oformat binary \
	    -Map kernel.map -o kernel.bin $(OBJS)	
	
clean:
	@echo kernel cleaning...
	@-rm kernel.map kernel.bin $(OBJS)

count:
	@echo dirs:  $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)
