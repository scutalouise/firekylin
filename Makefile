#
#    Makefile
#
#    Copyright (C) 2016 ximo<ximoos@foxmail.com>
#

AS=nasm
CC=gcc -fno-builtin -std=c99

all:
	make -C kernel
	make -C libc
	make -C command
	
install:
	make install -C kernel
	make install -C libc
	make install -C command
	sync
	sync
	cp   ~/hd.vhd hd.vhd
	sync
	sync
	
clean:
	make clean -C kernel
	make clean -C libc
	make clean -C command
	-rm  hd.vhd

count:
	@echo dirs:  $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)

qemu:
	qemu -hda hd.vhd

bochs:
	bochs -q -f script/bochsrc
	
bochsdbg:
	bochsdbg -q -f script/bochsrc
