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

SFLAGS=-g -f elf32 -g 
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include

OBJS=init/head.o init/main.o  \
     kernel/entry.o kernel/trap.o    kernel/util.o  \
     kernel/sched.o kernel/signal.o  kernel/timer.o \
     kernel/lock.o  kernel/softirq.o kernel/sys.o   \
     kernel/fork.o  kernel/exec.o    kernel/wait.o  \
     kernel/exit.o  kernel/trace.o \
     mm/memory.o \
     driver/char/tty_con.o driver/char/tty_kbd.o driver/char/tty_com.o \
     driver/char/tty_io.o  driver/char/mem.o \
     driver/block/ramdisk.o driver/block/floppy.o driver/block/atapi.o \
     driver/driver.o driver/pci.o driver/ne2k.o \
     fs/buffer.o fs/super.o fs/inode.o fs/read.o fs/stat.o fs/open.o \
     fs/write.o fs/fcntl.o fs/create.o fs/pipe.o fs/ioctl.o fs/close.o \
     fs/minix/super.o fs/minix/inode.o fs/minix/bitmap.o \
     fs/minix/namei.o fs/minix/file.o fs/minix/operation.o \
     lib/mktime.o lib/vsprintf.o lib/ctype.o lib/malloc.o
       
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
