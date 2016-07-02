#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

all: complie cdrom hdimg

complie:
	make -C kernel
	make -C lib
	make -C bin
	make -C test
	-make -C lua
	
cdrom:
	@make complie 2>&1 > /dev/null
	@sh script/mkiso.sh
	
hdimg:
	@sudo sh script/mkhdimg.sh
	
clean:
	make clean -C kernel
	make clean -C lib
	make clean -C bin
	make clean -C test
	-make clean -C lua
	-rm -rf iso
	-rm cdrom.iso hd.img

count:
	@sh script/countline.sh

qemu:
	qemu -net nic,model=ne2k_pci,vlan=1,macaddr=12:54:00:12:34:56 \
	     -boot d -cdrom cdrom.iso -hda hd.img

qemuS:
	qemu -net nic,model=ne2k_pci,vlan=1,macaddr=12:54:00:12:34:56 \
	     -S -gdb tcp::1234 -boot d -cdrom cdrom.iso -hda hd.img
	     
bochs:
	bochs -q -f script/bochsrc
	
bochsdbg:
	bochsdbg -q -f script/bochsrc
