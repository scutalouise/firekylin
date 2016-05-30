/*
 *    include/firekylin/minixfs_ext.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _MINIXFS_EXT_H
#define _MINIXFS_EXT_H

struct minix_inode_ext{
	unsigned short  i_zone[9];
};

struct minix_super_ext{
	unsigned short s_ninodes;
	unsigned short s_nzones;
	unsigned short s_imap_blocks;
	unsigned short s_zmap_blocks;
	unsigned short s_firstdatazone;
	unsigned short s_log_zone_size;
	unsigned long  s_max_size;
	unsigned short s_magic;
};

#endif
