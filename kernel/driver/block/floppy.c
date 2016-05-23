#include <arch/portio.h>
#include <arch/dma.h>
#include <arch/fdreg.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/trap.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>

char fd_buffer[1024]; 			/* 软盘高速缓冲区地址指针 */

#define MAX_REPLIES 7
static char  fd_reply[MAX_REPLIES]; 	/* 软驱回应缓冲区 */
#define ST0 (fd_reply[0])           	/* 软驱回应0号字节 */
#define ST1 (fd_reply[1])           	/* 软驱回应1号字节 */
#define ST2 (fd_reply[2])           	/* 软驱回应2号字节 */
#define ST3 (fd_reply[3])           	/* 软驱回应3号字节 */

static char *floppy_inc_name; 		/* 软驱型号名 */
static char *floppy_type;
static int   floppy_motor = 0; 		/* 软驱马达状态字节 */

int fd_result(void)
{
	int stat, i;
	i = 0;
	for (int count = 0; count < 0xffffff; count++) {
		stat = inb(FD_STATUS)
				& (STATUS_READY | STATUS_DIR | STATUS_BUSY);
		if (stat == STATUS_READY)
			return i;
		if (stat == (STATUS_READY | STATUS_DIR | STATUS_BUSY)) {
			if (i > 7)
				break;
			fd_reply[i++] = inb(FD_DATA);
		}
	}
	panic("Get floppy status times out !\n");
}

int fd_sendbyte(int value)
{
	int stat, i;

	for (i = 0; i < 0xfffff; i++) {
		stat = inb(FD_STATUS) & (STATUS_READY | STATUS_DIR);
		if (stat == STATUS_READY) {
			outb(FD_DATA,value);
			return 1;
		}
	}
	printk("Unable to send byte to FDC\n");
	return 0;
}

int fd_getbyte(void)
{
	int stat, i;

	for (i = 0; i < 0xfffff; i++) {
		stat = inb(FD_STATUS)
				& (STATUS_READY | STATUS_DIR | STATUS_BUSY);
		if (stat == STATUS_READY)
			return -1;
		if (stat == 0xD0)
			return inb(FD_DATA);
	}
	printk("Unable to get byte to FDC\n");
	return 0;
}

int fd_getinfo(void)
{
	int i;
	int CmType, FdType;

	fd_sendbyte(0x10);
	i = fd_getbyte();

	switch (i) {
		case 0x80:
			floppy_inc_name = "NEC765A controller";
			break;
		case 0x90:
			floppy_inc_name = "NEC765B controller";
			break;
		default:
			floppy_inc_name = "Enhanced controller";
			break;
	}

	CMOSREAD(CmType,0x10);        //read floppy type from cmos
	FdType = (CmType >> 4) & 0x07;

	if (FdType == 0)
		printk("Floppy driver not found!");

	switch (FdType) {
		case 0x02: // 1.2MB
			floppy_type = "1.2MB";
			break;

		case 0x04: // 1.44MB
			floppy_type = "1.44MB";
			break;

		case 0x05: // 2.88MB
			floppy_type = "2.88MB";
			break;
	}
	return 1;
}

void fd_motorOn(void)
{
	if (!floppy_motor) {
		irq_lock();
		outb(FD_DOR,28);
		floppy_motor = 1;
		irq_unlock();
	}
	return;
}

void fd_motorOff(void)
{
	if (floppy_motor) {
		irq_lock();
		outb(FD_DOR,12);
		floppy_motor = 0;
		irq_unlock();
	}
	return;
}

void fd_setmode(void)
{
	fd_sendbyte(FD_SPECIFY);
	fd_sendbyte(0xcf);
	fd_sendbyte(0x06);
	outb(FD_DCR,0);
}

void block_to_hts(int block, int *head, int *track, int *sector)
{
	*head = (block % (18 * 2)) / 18;
	*track = block / (18 * 2);
	*sector = block % 18 + 1;
}

void fd_setupDMA(void)
{
	//irq_lock();
	//DisableDma(2);
	//ClearDmaFF(2);
	//SetDmaMode(2, DMA_MODE_READ);
	//SetDmaAddr(2, (unsigned long) fd_buffer);
	//SetDmaCount(2, 512);
	//EnableDma(2);
	//irq_unlock();
}

void fd_read_cmd(int blk)
{
	int head,track,sector;

	block_to_hts(blk, &head, &track, &sector);

	fd_motorOn();
	fd_setupDMA();
	fd_setmode();
	fd_sendbyte(FD_READ);
	fd_sendbyte(head * 4 + 0);
	fd_sendbyte(track); 	/*  Cylinder  */
	fd_sendbyte(head); 	/*  Head  */
	fd_sendbyte(sector); 	/*  Sector  */
	fd_sendbyte(2); 	/*  0=128, 1=256, 2=512, 3=1024, ...  */
	fd_sendbyte(18);
	fd_sendbyte(0x1B);
	fd_sendbyte(0xff);
	return;
}

void fd_read(struct buffer *buf)
{

	fd_read_cmd(512);

	//task_ioblock(); /* 当前任务将陷入io等待中 */

	/* --------结果检查-------- */

	fd_result();

	if (ST1 != 0 || ST2 != 0) {
		panic("ST0 %d ST1 %d ST2 %d\n", ST0, ST1, ST2);
	}
	/* --------结果检查完成-------- */

	memcpy(buf->b_data, fd_buffer, 1024);

	fd_motorOff();
}

void fd_init(void)
{
	fd_getinfo();
	printk("Floppy Inc : %s  Floppy Type : %s",floppy_inc_name,floppy_type);
}
