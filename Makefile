#
#    Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc -fno-builtin -std=c99
HD=hd.img

build:boot/bootsect.bin tools/install-boot $(HD)
	make -C kernel
	make -C libc
	make -C command
	mkfs.minix -1 $(HD)
	sudo mount -t minix $(HD) -o loop /mnt
	-mkdir /mnt/boot
	-mkdir /mnt/bin
	-mkdir /mnt/dev
	-mkdir /mnt/etc
	-mkdir /mnt/home
	-mkdir /mnt/lib
	-mkdir /mnt/src
	-sudo mknod /mnt/dev/tty1 c 4 1
	-sudo mknod /mnt/dev/com1 c 4 2
	-sudo mknod /mnt/dev/ram0 b 1 0
	-sudo mknod /mnt/dev/hda  b 3 0
	-sudo mknod /mnt/dev/hda1 b 3 1
	-sudo mknod /mnt/dev/hda2 b 3 2
	-sudo mknod /mnt/dev/hda3 b 3 3
	-sudo mknod /mnt/dev/hda4 b 3 4
	cp   kernel/kernel.bin /mnt/boot/kernel
	cp   kernel/kernel.map /mnt/boot/kernel.map
	cp   command/init /mnt/bin/init
	cp   command/sh /mnt/bin/sh
	cp   command/ls /mnt/bin/ls
	cp   command/cat /mnt/bin/cat
	cp   command/sync /mnt/bin/sync
	cp   command/mkdir /mnt/bin/mkdir
	cp   command/touch /mnt/bin/touch
	cp   command/cp /mnt/bin/cp
	cp   command/ll /mnt/bin/ll
	cp   command/rm /mnt/bin/rm
	cp   command/ed /mnt/bin/ed
	cp   command/link /mnt/bin/link
	cp   command/*     /mnt/src/
	sudo umount /mnt
	./tools/install-boot boot/bootsect.bin $(HD)
	
clean:
	-rm -f boot/bootsect.bin
	-rm -f tools/install-boot
	-rm -f $(HD)
	@make clean -C kernel
	@make clean -C libc
	@make clean -C command

count:
	@echo dirs:  $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)

boot/bootsect.bin:boot/bootsect.s
	$(AS) -o $@  $<
	
tools/install-boot:tools/install-boot.c
	$(CC) -o $@  $<
	
$(HD):
	dd if=/dev/zero of=$(HD) bs=1024 count=4096
