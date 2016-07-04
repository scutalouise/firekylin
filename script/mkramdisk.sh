#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

# if don't have a ramdisk at $HOME ,then creat one

if [ ! -f ~/ramdisk.img ] ; then
	echo "creating ramdisk image file:$HOME/ramdisk.img"
	dd   if=/dev/zero of=$HOME/ramdisk.img bs=1024 count=6144 2> /dev/null
	echo "creating minix file system in image file:$HOME/ramdisk.img"
	sudo mkfs.minix -1 $HOME/ramdisk.img > /dev/null
fi

# create tmpdir to mount ramdisk

if [ ! -d ~/tmpdir ] ; then
	echo "creating tmpdir at $HOME\n"
	mkdir -p ~/tmpdir
fi

# mount ~/ramdisk image to ~/tmpdir

sudo mount -t minix -o loop $HOME/ramdisk.img $HOME/tmpdir
if [ ! $? ] ; then
	echo "mount error : mkramdisk failed !\n"
	exit
fi

# create needed dirs
echo "creating dirs"
sudo mkdir -p ~/tmpdir/bin
sudo mkdir -p ~/tmpdir/dev
sudo mkdir -p ~/tmpdir/boot
sudo mkdir -p ~/tmpdir/lib
sudo mkdir -p ~/tmpdir/home
sudo mkdir -p ~/tmpdir/test
sudo mkdir -p ~/tmpdir/etc


# create some test file 

sudo cp /etc/crontab ~/tmpdir/etc/crontab
sudo cp /etc/shadow  ~/tmpdir/etc/shadow
sudo cp /etc/shells  ~/tmpdir/etc/shells
sudo cp /etc/mtab    ~/tmpdir/etc/mtab
sudo cp /etc/fstab   ~/tmpdir/etc/fstab

# create dev spciel node 

echo "creating dev nodes"
sudo mknod ~/tmpdir/dev/mem  c  1  1
sudo mknod ~/tmpdir/dev/port c  1  2
sudo mknod ~/tmpdir/dev/null c  1  3
sudo mknod ~/tmpdir/dev/full c  1  4

sudo mknod ~/tmpdir/dev/tty  c  2  0
sudo mknod ~/tmpdir/dev/tty1 c  2  1
sudo mknod ~/tmpdir/dev/tty2 c  2  2
sudo mknod ~/tmpdir/dev/tty3 c  2  3

sudo mknod ~/tmpdir/dev/com1 c  2  4
sudo mknod ~/tmpdir/dev/com2 c  2  5

sudo mknod ~/tmpdir/dev/rd   b  1  0

sudo mknod ~/tmpdir/dev/fd0  b  2  0
#sudo mknod ~/tmpdir/dev/fd1  b  2  1

sudo mknod ~/tmpdir/dev/hda  b  3  0
sudo mknod ~/tmpdir/dev/hda1 b  3  1
sudo mknod ~/tmpdir/dev/hda2 b  3  2
#sudo mknod ~/tmpdir/dev/hda3 b  3  3
#sudo mknod ~/tmpdir/dev/hda4 b  3  4

# umount the ramdisk

sudo umount $HOME/ramdisk.img

if [ ! $? ]; then
	echo "warning:umount failed !"
fi
