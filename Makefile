#
#    Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc -fno-builtin -std=c99

default:
	@echo default todo nothing
	
boot/boot.bin:boot/boot.s
	$(AS) -o $@  $<

kernel/kernel.bin:
	make -C kernel
	
libc/libc.a:
	make -C libc

commands:
	make -C command

tools/build:tools/build.c
	$(CC) -o $@  $<

boot.img:boot/boot.bin kernel/kernel.bin tools/build
	./tools/build boot/boot.bin kernel/kernel.bin boot.img

root.img:
	dd if=/dev/zero of=root.img bs=512 count=20480
	
install:kernel/kernel.bin libc/libc.a commands root.img
	mkfs.minix -1 root.img
	mount -t minix root.img -o loop /mnt
	-mkdir /mnt/boot
	-mkdir /mnt/bin
	-mkdir /mnt/dev
	-mkdir /mnt/etc
	-mkdir /mnt/home
	-mkdir /mnt/lib
	-mknod /mnt/dev/tty1 c 4 1
	-mknod /mnt/dev/com1 c 4 2
	cp   kernel/kernel.bin /mnt/boot/kernel
	cp   kernel/kernel.map /mnt/boot/kernel.map
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
	cp   command/rm /mnt/bin/rm
	cp   command/ed /mnt/bin/ed
	cp   command/link /mnt/bin/link
	umount root.img
	
clean:
	-rm boot/boot.bin tools/build boot.img root.img
	make clean -C kernel
	make clean -C libc
	make clean -C command
run: 
	bochs -q -f bochsrc

dbg: 
	bochsdbg -q -f bochsrc

count:
	@echo dirs: $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)
