#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

# Note: make flat format image, support by bochs and qemu, other will not.
#       if exec file twice again, it will make something wrong. 

# image file size 256MB.
SIZE=256

# create image file 
	
echo "create hd.img ... "
dd if=/dev/zero of=$HOME/hd.img bs=1024 count=$(( $SIZE * 1024)) 2> /dev/null

# create partion

echo "create partion ... "
echo -e "o\n n\n p\n 1\n \n +64M\n n\n p\n 2\n \n +64M\n w\n w\n " | \
fdisk $HOME/hd.img 2>&1 > /dev/null

# Note:assume map to /dev/loop0, if not something goes wrong.

echo "kpartx mappimg hd.img ... "
sudo kpartx -av $HOME/hd.img 2>&1 > /dev/null

sudo mkfs.minix -1 /dev/mapper/loop0p1 2>&1 > /dev/null
sudo mkfs.minix -1 /dev/mapper/loop0p2 2>&1 > /dev/null

mkdir -p $HOME/part1 $HOME/part2

sudo mount -t minix /dev/mapper/loop0p1 $HOME/part1 2>&1 > /dev/null
sudo mount -t minix /dev/mapper/loop0p2 $HOME/part2 2>&1 > /dev/null

echo "creating test file ..."

sudo echo "The test file 1" > $HOME/part1/test1.txt
sudo echo "The test file 2" > $HOME/part1/test2.txt
sudo echo "The test file 3" > $HOME/part1/test3.txt

sudo echo "The test file 4" > $HOME/part2/test4.txt
sudo echo "The test file 5" > $HOME/part2/test5.txt
sudo echo "The test file 6" > $HOME/part2/test6.txt

sudo umount /dev/mapper/loop0p1 2>&1 > /dev/null
sudo umount /dev/mapper/loop0p2 2>&1 > /dev/null

sudo kpartx -dv $HOME/hd.img 2>&1 > /dev/null

sync
sync
cp   $HOME/hd.img hd.img
sync
sync
