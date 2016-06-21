/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_ARP_H
#define _NET_ARP_H

#include <net/ether.h>

#define	ARP_HADDR_LEN	ETH_ADDR_LEN	/* Size of Ethernet MAC address	*/
#define	ARP_PADDR_LEN	4		/* Size of IP address		*/


struct arphdr{
	unsigned short ah_htype;
	unsigned short ah_ptype;
	unsigned char  ah_haddr_len;
	unsigned char  ah_paddr_len;
	unsigned short ah_op;
	unsigned char  ah_src_haddr[ARP_HADDR_LEN];
	unsigned char  ah_src_paddr[ARP_PADDR_LEN];
	unsigned char  ah_target_haddr[ARP_HADDR_LEN];
	unsigned char  ah_target_paddr[ARP_PADDR_LEN];
};

/* Values of arphdr->ah_htype */
#define ARP_HTYPE_ETHER		1	/* Ethernet hardware type	*/

/* Values of arphdr->ah_ptype */
#define ARP_PTYPE_IP		0x0800	/* IP protocol type		*/

/* Values of arphdr->ah_op    */
#define ARP_OP_REQUEST		1	/* Request op code		*/
#define ARP_OP_REPLY		2	/* Reply op code		*/

struct arpentry{
	struct aprentry *prev;
	struct aprentry *next;
	unsigned char mac[ARP_HADDR_LEN];
	unsigned char ip[ARP_PADDR_LEN];
};

#endif
