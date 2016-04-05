#
#    Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc

all:System.img libc/libc.a commands

System.img:boot/boot.bin kernel/kernel.bin tools/build
	./tools/build boot/boot.bin kernel/kernel.bin System.img
	
tools/build:tools/build.c
	$(CC) -o $@  $<

boot/boot.bin:boot/boot.s
	$(AS) -o $@  $<

kernel/kernel.bin:
	make -C kernel
	
libc/libc.a:
	make -C libc

commands:
	make -C command

install:commands
	-rm hd.img
	dd if=/dev/zero of=hd.img bs=512 count=20480
	mkfs.minix -1 hd.img
	mount -t minix hd.img -o loop /mnt
	mkdir /mnt/bin
	mkdir /mnt/dev
	mkdir /mnt/etc
	mknod /mnt/dev/tty1 c 4 1
	mknod /mnt/dev/com1 c 4 2
	cp   command/init /mnt/bin/init
	cp   command/sh /mnt/bin/sh
	cp   command/ls /mnt/bin/ls
	cp   command/echo /mnt/bin/echo
	cp   command/cat /mnt/bin/cat
	cp   command/sync /mnt/bin/sync
	cp   command/mkdir /mnt/bin/mkdir
	cp   command/touch /mnt/bin/touch
	cp   command/cp /mnt/bin/cp
	cp   command/ll /mnt/bin/ll
	cp   command/rename /mnt/bin/rename
	cp   command/rm /mnt/bin/rm
	cp   command/ed /mnt/bin/ed
	cp   command/link /mnt/bin/link
	tree /mnt
	umount hd.img
clean:
	-rm boot/boot.bin tools/build system.img hd.img
	make clean -C kernel
	make clean -C libc
	make clean -C command
	
run: system.img
	bochs -q -f bochsrc

dbg: system.img
	bochsdbg -q -f bochsrc

count:
	@echo dirs: $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)
