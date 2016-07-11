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
       -fno-stack-protector -I ../include

OBJS=init/head.o  init/main.o  \
     kern/entry.o kern/trap.o    kern/util.o  \
     kern/sched.o kern/signal.o  kern/timer.o \
     kern/lock.o  kern/softirq.o kern/sys.o   \
     kern/fork.o  kern/exec.o    kern/wait.o  kern/exit.o  kern/trace.o \
     mm/memory.o \
     dev/dev.o   dev/char/mem.o \
     dev/char/tty_con.o  dev/char/tty_kbd.o dev/char/tty_com.o \
     dev/char/tty_io.o \
     dev/block/ramdisk.o dev/block/atapi.o \
     dev/pci.o        dev/ne2k.o \
     fs/buffer.o fs/super.o fs/inode.o  fs/read.o fs/stat.o  fs/open.o  \
     fs/write.o  fs/fcntl.o fs/create.o fs/pipe.o fs/ioctl.o fs/close.o \
     fs/minix/super.o fs/minix/inode.o fs/minix/bitmap.o \
     fs/minix/namei.o fs/minix/file.o  fs/minix/operation.o \
     net/skbuf.o net/inet.o \
     klib/ctype.o    klib/mktime.o   klib/vsprintf.o 
       
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
	@ld -m elf_i386 -e _start -Ttext 0xC0010000  \
	    -Map kernel.map -o kernel.elf $(OBJS)
	
install:kernel.bin
	cp kernel.bin $(PREFIX)/kernel.bin
	
clean:
	@echo kernel cleaning...
	@-rm kernel.map kernel.bin kernel.elf $(OBJS)
