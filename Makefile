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
	make -C libc
	make -C command
	
cdrom: 
	@make complie 2>&1 > /dev/null
	@sh script/mkiso.sh
	
hdimg:
	@sudo sh script/mkhdimg.sh
	
clean:
	make clean -C kernel
	make clean -C libc
	make clean -C command
	-rm -rf iso
	-rm cdrom.iso hd.img

count:
	@sh script/countline.sh

qemu:
	qemu -net nic,model=ne2k_pci,vlan=1,macaddr=12:54:00:12:34:56 \
	     -net socket,vlan=1,listen=127.0.0.1:8087 \
	     -boot d -cdrom cdrom.iso -hda hd.img

bochs:
	bochs -q -f script/bochsrc
	
bochsdbg:
	bochsdbg -q -f script/bochsrc
