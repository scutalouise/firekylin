/*
 *    driver/block/hd.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/hd.h>
#include <firekylin/fs.h>

struct request{
	unsigned long LBA;
	unsigned char busy;
	unsigned char cmd;
	unsigned char nr_sect;
	unsigned char errors;
	unsigned long start_sect;
	char          *buf;
	struct buffer *bh;
	struct task   *wait;
};

static struct request hd_req;

static int ctl_ready()
{
	int r=0xffff;
	while(--r && (inb(HD_STATUS)&0x80));
	return r;
}

static void hd_out_cmd(int sector, int nr, int cmd)
{
	union {
		char arg[4];
		int sec;
	} sect;
	sect.sec = sector;
	if(!ctl_ready()){
		panic("hd outtime");
	}
	outb(0x3f6, 8);
	outb(0x1f1, 0);
	outb(0x1f2, nr);
	outb(0x1f3, sect.arg[0]);
	outb(0x1f4, sect.arg[1]);
	outb(0x1f5, sect.arg[2]);
	outb(0x1f6, (sect.arg[3]&0x0f)+0xe0);
	outb(0x1f7, cmd);
}

static void ide_read(struct buffer *buffer)
{
	irq_lock();
	while (hd_req.busy)
		sleep_on(&hd_req.wait);
	hd_req.busy = 1;
	hd_req.cmd = WIN_READ;
	hd_req.start_sect=buffer->b_block*2;
	hd_req.nr_sect=2;
	hd_req.bh=buffer;
	hd_req.buf=buffer->b_data;
	hd_out_cmd(buffer->b_block * 2, 2, WIN_READ);
	irq_unlock();
}

static void ide_write(struct buffer *buffer)
{
	char tmp;
	irq_lock();
	while (hd_req.busy)
		sleep_on(&hd_req.wait);
	hd_req.busy = 1;
	hd_req.cmd = WIN_WRITE;
	hd_req.start_sect=buffer->b_block*2;
	hd_req.nr_sect=2;
	hd_req.bh=buffer;
	hd_req.buf=buffer->b_data;
	hd_out_cmd(buffer->b_block * 2, 2, WIN_WRITE);
	do {
		tmp = inb(HD_STATUS);
	} while ((tmp & (HD_STAT_BUSY | HD_STAT_DRQ)) != HD_STAT_DRQ);

	outs(HD_DATA, buffer->b_data, 512);
	irq_unlock();
}

static void do_hd(struct trapframe *tf)
{
	char hd_status;
	
	outb(0xa0, 0x20);
	outb(0x20, 0x20);
	
	hd_status = inb(HD_STATUS);

	if ((hd_status & 0xf1) != 0x50) {
		panic("HD error %x", inb(HD_ERROR));
	}

	if (hd_req.cmd == WIN_READ) {
		ins(HD_DATA, hd_req.buf, 512);
		hd_req.buf += 512;
		if (--hd_req.nr_sect)
			return;
		hd_req.bh->b_flag = B_VALID;
		wake_up(&(hd_req.bh->b_wait));
		hd_req.buf = NULL;
		hd_req.busy = 0;
		hd_req.bh=NULL;
		wake_up(&(hd_req.wait));
		return ;
	}

	if (hd_req.cmd == WIN_WRITE) {
		hd_req.buf += 512;
		if (--hd_req.nr_sect){
			outs(HD_DATA, hd_req.buf, 512);
			return;
		}
		hd_req.bh->b_flag &=~B_DIRTY ;
		wake_up(&(hd_req.bh->b_wait));
		hd_req.buf = NULL;
		hd_req.busy = 0;
		hd_req.bh=NULL;
		wake_up(&(hd_req.wait));
		return ;
	}
}

static void hd_identify(void)
{
	short buf[256];
	char tmp;

	hd_out_cmd(0, 0, WIN_IDENTIFY);
	do {
		tmp = inb(HD_STATUS);
	} while ((tmp & (HD_STAT_BUSY | HD_STAT_DRQ)) != HD_STAT_DRQ);
	ins(0x1f0, (char*)buf, 512);

	hd_req.LBA = buf[60] | buf[61] << 16;
}

static struct blk_dev ide = { "ATA HD", NULL, NULL, ide_read, ide_write, NULL };

void hd_init(void)
{	
	hd_identify();
	set_trap_handle(0x2e, do_hd);
	outb(0xa1, inb(0xa1)&0xbf);
	blk_table[DEV_BLK_IDE] = &ide;
}
