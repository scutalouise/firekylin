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

boot/bootsect.bin:boot/bootsect.s
	$(AS) -o $@  $<

kernel/kernel.bin:
	make -C kernel
	
libc/libc.a:
	make -C libc

commands:
	make -C command

tools/build:tools/build.c
	$(CC) -o $@  $<

tools/install-boot:tools/install-boot.c
	$(CC) -o $@  $<

floppy.img:boot/boot.bin kernel/kernel.bin tools/build
	./tools/build boot/boot.bin kernel/kernel.bin floppy.img

hd.img:
	dd if=/dev/zero of=hd.img bs=512 count=20480
	
install:boot/bootsect.bin kernel/kernel.bin libc/libc.a commands \
        tools/install-boot hd.img
	mkfs.minix -1 hd.img
	mount -t minix hd.img -o loop /mnt
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
	cp   command/rename /mnt/bin/rename
	cp   command/rm /mnt/bin/rm
	cp   command/ed /mnt/bin/ed
	cp   command/link /mnt/bin/link
	umount hd.img
	./tools/install-boot boot/bootsect.bin hd.img
	
clean:
	-rm boot/boot.bin boot/bootsect.bin
	make clean -C kernel
	make clean -C libc
	make clean -C command
	-rm tools/build tools/install-boot
	-rm floppy.img hd.img

build:clean install

run: 
	bochs -q -f bochsrc

dbg: 
	bochsdbg -q -f bochsrc

count:
	@echo dirs: $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)
