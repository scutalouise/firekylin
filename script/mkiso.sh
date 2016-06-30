#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

# if dir iso/boot/grub not exist, creat it .

if [ ! -d iso/boot/grub ]; then
	echo  "creating dir iso/boot/grub"
	mkdir -p iso/boot/grub
fi

# if file iso/boot/grub/grub.cfg not exist, copy one.

if [ ! -f iso/boot/grub/grub.cfg ]; then
	echo  "creating file iso/boot/grub/grub.cfg"
	cp    script/grub.cfg     iso/boot/grub/grub.cfg
fi

# copy kernel binary 

echo "copying kernel to iso/boot/kernel.bin"
cp kernel/kernel.bin   iso/boot/kernel.bin

# if file none.img not
if [ ! -f iso/boot/none ]; then
	echo "creating file iso/boot/none.img"
	dd if=/dev/zero of=iso/boot/none.img bs=1024 count=1024 2> /dev/null
fi

# if $HOME/ramdisk.img not exist, create one .

if [ ! -f $HOME/ramdisk.img ]; then
	sh script/mkramdisk.sh
fi

# if $HOME/tmpdir not exist, create one .

if [ ! -d $HOME/tmpdir ]; then
	mkdir -p $HOME/tmpdir
fi
	
# mount $HOME/ramdisk.img to $HOME/tmpdir

sudo mount -t minix -o loop $HOME/ramdisk.img $HOME/tmpdir

if [ ! $? ]; then 
	echo "mount error: mkiso failed !"
	exit
fi

echo "installing bin ..."
sudo make PREFIX=$HOME/tmpdir/bin  install -C bin 2>&1 > /dev/null

echo "installing test ..."
sudo make PREFIX=$HOME/tmpdir/test  install -C test 2>&1 > /dev/null

echo "installing lua ..."
sudo make PREFIX=$HOME/tmpdir/bin  install -C lua 2>&1 > /dev/null

sync
sync
sudo umount $HOME/ramdisk.img

# copy $HOME/ramdisk.img to iso/boot/ramdisk.img

echo "creating iso/boot/ramdisk.img ..."
cp $HOME/ramdisk.img iso/boot/ramdisk.img
sync
sync

# create sourec pack.

if [ ! -f iso/src.tgz ] ; then
	echo "creating source tar ..."
	tar -zcf iso/src.tgz `ls | grep -v iso `
fi

# create VERSION.
echo "creating VERSION ... "
date > iso/VERSION

# creat cdrom.

echo "creating cdrom.iso ..."
grub-mkrescue -o cdrom.iso iso 2> /dev/null

if [ ! $? ]; then
	echo "Error: create cdrom.iso failed !"
fi
