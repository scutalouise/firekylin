/*
 *    fs/super.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/stat.h>
#include <sys/errno.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>

#define NR_SUPER	4
static struct super super_table[NR_SUPER];
static sleeplock_t super_lock;

#define lock_super_table()	require_lock(&super_lock);
#define unlock_super_table()	release_lock(&super_lock);

struct super * get_super(dev_t dev)
{
	struct super *super = super_table;

	lock_super_table();
	while (super < super_table + NR_SUPER) {
		if (super->s_dev == dev) {
			super->s_count++;
			unlock_super_table();
			lock_super(super);
			return super;
		}
		super++;
	}
	printk("Super Block NOT Load %x", dev);
	return NULL;
}

void put_super(struct super *super)
{
	if (!super)
		panic("put NULL super block");

	if (--super->s_count < 0)
		panic("put free super block");

	unlock_super(super);
}

int sys_mount(char *dev_name, char *dir_name, long ro_flag)
{
	struct inode *dev_i, *dir_i;
	struct super *super;
	int dev;

	if(!(dev_i=namei(dev_name,NULL)))
		return -ENOENT;
	if(!S_ISBLK(dev_i->i_mode)){
		printk("Not a block dev %s:%x",dev_name,dev_i->i_rdev);
		iput(dev_i);
		return -EPERM;
	}
	dev=dev_i->i_rdev;
	iput(dev_i);

	if(!(dir_i=namei(dir_name,NULL)))
		return -ENOENT;
	if(dir_i->i_count!=1 || dir_i->i_ino==1){
		iput(dir_i);
		return -EBUSY;
	}
	if(!S_ISDIR(dir_i->i_mode)){
		iput(dir_i);
		return -EPERM;
	}

	lock_super_table();
	for(super=super_table;super<super_table+NR_SUPER;super++)
		if(!super->s_dev)
			break ;
	if(super>=super_table+NR_SUPER){
		unlock_super_table();
		iput(dir_i);
		printk("super table use over");
		return -EAGAIN;
	}
	lock_super(super);
	unlock_super_table();

	super->s_dev=dev;
	super->s_op=&minix_fs_operation;
	if(super->s_op->super_read(super)<0){
		iput(dir_i);
		super->s_dev=0;
		unlock_super(super);
		return -EBUSY;
	}

	super->s_imount=dir_i;
	dir_i->i_flag |=(I_MOUNT|I_DIRTY);
	iunlock(dir_i);
	return 0;
}

int sys_umount(char *dev_name)
{
	struct inode *inode;
	struct super *super;
	int dev;

	if(!(inode=namei(dev_name,NULL)))
		return -ENOENT;
	if(!S_ISBLK(inode->i_mode)){
		iput(inode);
		return -ENOTBLK;
	}
	dev=inode->i_rdev;
	iput(inode);
	if(dev==ROOT_DEV)
		return -EBUSY;
	if(!(super=get_super(dev))|| !(super->s_imount))
		return -ENOENT;

	if(!(super->s_imount->i_flag& I_MOUNT))
		printk("Mounted inode has flag without I_MOUNT\n");
	//for(inode=inode_table;inode <inode_table +NR_INODE;inode++)
	//	if(inode->i_dev==dev && inode->i_count)
	//		return -EBUSY;
	super->s_imount->i_flag &=~I_MOUNT;
	iput(ilock(super->s_imount));
	super->s_dev=0;
	put_super(super);
	return -ERROR;
}

void mount_root(void)
{
	extern struct inode *root_inode;
	struct super *super = super_table;
	struct task *task = CURRENT_TASK();

	super->s_dev = ROOT_DEV;
	super->s_op = &minix_fs_operation;
	super->s_op->super_read(super);
	root_inode = iunlock(iget(ROOT_DEV, 1));
	task->pwd = iunlock(idup(root_inode));
}
