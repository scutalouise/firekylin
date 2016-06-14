#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

AS=nasm
CC=gcc -fno-builtin -std=c99

all:
	make -C kernel
	make -C libc
	make -C command
	
cdrom: 
	@echo complie ...
	@make all 2>&1 > /dev/null
	@sh script/mkiso.sh
	
clean:
	make clean -C kernel
	make clean -C libc
	make clean -C command
	-rm -rf iso
	-rm cdrom.iso

count:
	@echo dirs:  $(shell ls -lR |grep ^d |wc -l)
	@echo files: $(shell ls -lR |grep ^- |wc -l)
	@echo lines: $(shell find . -name *.[chs] |xargs grep -v ^$$ |wc -l)

qemu:
	qemu -net nic,model=rtl8139,vlan=1,macaddr=52:54:00:12:34:56 \
	     -cdrom cdrom.iso

bochs:
	bochs -q -f script/bochsrc
	
bochsdbg:
	bochsdbg -q -f script/bochsrc
