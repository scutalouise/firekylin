#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

SUM_DIR=0
SUM_FILE=0
SUM_LINE=0

for dir in include kernel lib bin test ;
do
	DIR=`ls -lR $dir |grep ^d |wc -l`
	FILE=`ls -lR $dir |grep ^- |wc -l`
	LINE=`find $dir -name *.[chs] |xargs grep -v ^$$ |wc -l`
	
	# not count head commit .
	LINE=$(( $LINE - 9 * $FILE ))
	
	echo $dir
	echo "    subdir:" $DIR
	echo "    file  :" $FILE
	echo "    line  :" $LINE
	
	SUM_DIR=$(( $SUM_DIR  + $DIR  ))
	SUM_FILE=$(( $SUM_FILE + $FILE ))
	SUM_LINE=$(( $SUM_LINE + $LINE ))
done

echo "All"
echo "    subdir:" $SUM_DIR
echo "    file  :" $SUM_FILE
echo "    line  :" $SUM_LINE
