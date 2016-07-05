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

OBJS=init_head.o  init_main.o  \
     kern_entry.o kern_trap.o    kern_util.o  \
     kern_sched.o kern_signal.o  kern_timer.o \
     kern_lock.o  kern_softirq.o kern_sys.o   kern_dev.o \
     kern_fork.o  kern_exec.o    kern_wait.o  kern_exit.o  kern_trace.o \
     vm_memory.o \
     chrdev_mem.o \
     chrdev_tty_con.o chrdev_tty_kbd.o chrdev_tty_com.o chrdev_tty_io.o \
     blkdev_ramdisk.o blkdev_atapi.o \
     dev_pci.o        dev_ne2k.o \
     vfs_buffer.o vfs_super.o vfs_inode.o  vfs_read.o vfs_stat.o  vfs_open.o  \
     vfs_write.o  vfs_fcntl.o vfs_create.o vfs_pipe.o vfs_ioctl.o vfs_close.o \
     minixfs/super.o minixfs/inode.o minixfs/bitmap.o \
     minixfs/namei.o minixfs/file.o  minixfs/operation.o \
     klib_ctype.o    klib_mktime.o   klib_vsprintf.o 
       
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
