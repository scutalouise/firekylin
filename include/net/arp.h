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

#define	ARP_MAC_LEN	6		/* Size of Ethernet MAC address	*/
#define	ARP_IPADDR_LEN	4		/* Size of IP address		*/

#define	ARP_HTYPE	1		/* Ethernet hardware type	*/
#define ARP_PTYPE	0x0800		/* IP protocol type		*/

#define ARP_OP_REQ	1		/* Request op code		*/
#define ARP_OP_RPLY	2		/* Reply op code		*/

#define	ARP_ENTER_SIZE	16		/* Number of entries in a cache	*/

#define	ARP_REQUSET	4		/* Num. retries for ARP request	*/

#define	ARP_TIMEOUT	300		/* Retry timer in milliseconds	*/

#define	AR_FREE		0		/* Slot is unused		*/
#define	AR_PENDING	1		/* Resolution in progress	*/
#define	AR_RESOLVED	2		/* Entry is valid		*/

#pragma pack(2)
struct arpkpt{
	struct ethhdr  arp_ethhdr;
	unsigned short arp_htype;
	unsigned short arp_ptype;
	unsigned char  arp_mac_len;
	unsigned char  arp_ipaddr_len;
	unsigned char  arp_op;
	unsigned char  arp_src_mac[ARP_MAC_LEN];
	unsigned char  arp_src_ipaddr[ARP_IPADDR_LEN];
	unsigned char  arp_target_mac[ARP_MAC_LEN];
	unsigned char  arp_target_ipaddr[ARP_IPADDR_LEN];
};
#pragma pack()

struct arpentry{
	struct aprentry *prev;
	struct aprentry *next;
	unsigned char mac[ARP_MAC_LEN];
	unsigned char ip[ARP_IPADDR_LEN];
};

#endif
