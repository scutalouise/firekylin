/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_ETHER_H
#define _NET_ETHER_H

#define ETH_ADDR_LEN	6

struct ethhdr{
	unsigned char  dst[ETH_ADDR_LEN];
	unsigned char  src[ETH_ADDR_LEN];
	unsigned short type;
	unsigned char  data[0];	/* size 46-1500 */
};

#define ETH_HDR_LEN	14

#define ETH_MTU		1500
#define ETH_VLAN_LEN	4
#define ETH_CRC_LEN	4

#define ETH_PKT_MAX_LEN	(ETH_HDR_LEN + ETH_VLAN_LEN +ETH_MTU)

#endif
