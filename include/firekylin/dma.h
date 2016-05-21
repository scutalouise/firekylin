/*
 *    include/firekylin/dma.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _DMA_H
#define _DMA_H

#define DMA_CHANNELS		8

/* 8237 DMA controllers */
#define DMA1_BASE	    0x00        /* 8 bit slave DMA, channels 0..3 */
#define DMA2_BASE	    0xC0        /* 16 bit master DMA, channels 4..7 */

/* DMA controller registers */
#define DMA1_CMD            0x08        /* command register (w) */
#define DMA1_STAT           0x08        /* status register (r) */
#define DMA1_REQ            0x09        /* request register (w) */
#define DMA1_MASK           0x0A        /* single-channel mask (w) */
#define DMA1_MODE           0x0B        /* mode register (w) */
#define DMA1_CLEAR_FF       0x0C        /* clear pointer flip-flop (w) */
#define DMA1_TEMP           0x0D        /* Temporary Register (r) */
#define DMA1_RESET          0x0D        /* Master Clear (w) */
#define DMA1_CLR_MASK       0x0E        /* Clear Mask */
#define DMA1_MASK_ALL       0x0F        /* all-channels mask (w) */

#define DMA2_CMD            0xD0        /* command register (w) */
#define DMA2_STAT           0xD0        /* status register (r) */
#define DMA2_REQ            0xD2        /* request register (w) */
#define DMA2_MASK           0xD4        /* single-channel mask (w) */
#define DMA2_MODE           0xD6        /* mode register (w) */
#define DMA2_CLEAR_FF       0xD8        /* clear pointer flip-flop (w) */
#define DMA2_TEMP           0xDA        /* Temporary Register (r) */
#define DMA2_RESET          0xDA        /* Master Clear (w) */
#define DMA2_CLR_MASK       0xDC        /* Clear Mask */
#define DMA2_MASK_ALL       0xDE        /* all-channels mask (w) */

#define DMA_ADDR_0          0x00        /* DMA address registers */
#define DMA_ADDR_1          0x02
#define DMA_ADDR_2          0x04
#define DMA_ADDR_3          0x06
#define DMA_ADDR_4          0xC0
#define DMA_ADDR_5          0xC4
#define DMA_ADDR_6          0xC8
#define DMA_ADDR_7          0xCC

#define DMA_CNT_0           0x01        /* DMA count registers */
#define DMA_CNT_1           0x03
#define DMA_CNT_2           0x05
#define DMA_CNT_3           0x07
#define DMA_CNT_4           0xC2
#define DMA_CNT_5           0xC6
#define DMA_CNT_6           0xCA
#define DMA_CNT_7           0xCE

#define DMA_PAGE_0          0x87        /* DMA page registers */
#define DMA_PAGE_1          0x83
#define DMA_PAGE_2          0x81
#define DMA_PAGE_3          0x82
#define DMA_PAGE_5          0x8B
#define DMA_PAGE_6          0x89
#define DMA_PAGE_7          0x8A

#define DMA_MODE_READ       0x44        /* I/O to memory, no autoinit, increment, single mode */
#define DMA_MODE_WRITE      0x48        /* memory to I/O, no autoinit, increment, single mode */
#define DMA_MODE_CASCADE    0xC0        /* pass thru DREQ->HRQ, DACK<-HLDA only */

#endif
