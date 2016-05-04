/*
 *    tools/install-boot.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 *
 *  Usage: install-boot boot.bin dev_name
 *      such as: install-boot boot/boot.bin hd.img
 *
 *  not used
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct super {
	unsigned short s_ninodes;
	unsigned short s_nzones;
	unsigned short s_imap_blocks;
	unsigned short s_zmap_blocks;
	unsigned short s_firstdatazone;
	unsigned short s_log_zone_size;
	unsigned int   s_max_size;
	unsigned short s_magic;
};

struct inode {
	unsigned short i_mode;
	unsigned short i_uid;
	unsigned int   i_size;
	unsigned int   i_time;
	unsigned char  i_gid;
	unsigned char  i_nlinks;
	unsigned short i_zone[9];
};

#define NAME_LEN	30
struct dirent {
	unsigned short d_ino;
	char           d_name[NAME_LEN];
};

#define memcpy(dst,src,size)		\
    __asm__("rep movsb":: "D"(dst),"S"(src),"c"(size));
    
#define memset(s,c,size)		\
    __asm__("rep stosb" ::"D"(s),"a"(c),"c"(size));

struct super super_block;

int strncmp(char *s1, char *s2, int n)
{
	while (n--) {
		if (*s1 && (*s1 == *s2)) {
			s1++;
			s2++;
		} else {
			return (*s1 - *s2);
		}
	}
	return 0;
}  

void read_block(FILE *fp,int block,char *buf)
{
	fseek(fp,block*1024,0);
	fread(buf,1,1024,fp);
}

void read_super(FILE *fp)
{
	fseek(fp,1024,0);
	fread(&super_block,1,sizeof(struct super),fp);
}

void read_inode(FILE *fp,int ino,struct inode *pinode)
{
	char buf[1024];
	int block=2+super_block.s_imap_blocks+super_block.s_zmap_blocks+(ino-1)*sizeof(struct inode)/1024;
	int off=(ino-1)*sizeof(struct inode)%1024;
	read_block(fp,block,buf);
	memcpy((char*)pinode,buf+off,sizeof(struct inode));
}

void look_up(FILE *fp,struct inode *pinode,char *name)
{
	char buf[1024];
	struct dirent *de;
	int i;

	read_block(fp,pinode->i_zone[0],buf);
	de=(struct dirent *)buf;
	for(i=0;i<1024/sizeof(struct dirent);i++){
		if(!strncmp(de->d_name,name,30)){
			read_inode(fp,de->d_ino,pinode);
			return;
		}
		de++;
	}
	printf("can not find %s\n",name);
	exit(0);
}

int main(int argc, char **argv)
{
	FILE *boot, *img;
	char boot_buf[512];
	short buf2[512];
	short blocks[256];
	struct inode inode;
	int i=0;
	
	if (argc != 3) {
		fprintf(stderr, "install-boot boot.bin dev_name\n");
		exit(0);
	}

	boot = fopen(argv[1], "rb");
	if (boot == NULL) {
		fprintf(stderr, "File Open Error:%s", argv[3]);
		exit(0);
	}
	
	img = fopen(argv[2], "r+");
	if (img == NULL) {
		fprintf(stderr, "File Open Error:%s", argv[1]);
		exit(0);
	}

	fread(boot_buf, 512, 1, boot);
	fclose(boot);
	
	read_super(img);

	read_inode(img,1,&inode);

	look_up(img,&inode,"boot");
	look_up(img,&inode,"kernel");

	memset(blocks,0,512);
	for(i=0;i<7;i++)
		blocks[i]=inode.i_zone[i];

	read_block(img,inode.i_zone[7],(char*)buf2);
	while(i*1024<inode.i_size){
		blocks[i]=buf2[i-7];
		i++;
	}
	
	fseek(img,0,0);
	fwrite(boot_buf,1,512,img);
	fwrite(blocks,1,512,img);
	fclose(img);
}
