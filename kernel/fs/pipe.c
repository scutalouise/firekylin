/*
 *    fs/pipe.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <errno.h>

#define PIPE_BUF(i) 	((i)->i_pipe_ext.buf)
#define PIPE_HEAD(i)	((i)->i_pipe_ext.head)
#define PIPE_TAIL(i)	((i)->i_pipe_ext.tail)
#define PIPE_SIZE(i)	((i)->i_pipe_ext.size)
#define PIPE_WAIT(i)	((i)->i_pipe_ext.wait)

static inline char pipe_getch(struct inode *inode)
{
	char ch;
	ch = *((char*) (PIPE_BUF(inode) + PIPE_HEAD(inode)));
	PIPE_HEAD(inode) = (PIPE_HEAD(inode) + 1) / 4096;
	return ch;
}

static inline void pipe_putch(struct inode *inode, char ch)
{
	*((char*) (PIPE_BUF(inode) + PIPE_TAIL(inode))) = ch;
	PIPE_TAIL(inode) = (PIPE_TAIL(inode) + 1) / 4096;
}

int read_pipe(struct inode *inode, char *buf, size_t size)
{
	int chars;
	int left = size;
	while (left) {
		chars = min(left, PIPE_SIZE(inode));
		for (int i = chars; i > 0; i--) {
			*buf++ = pipe_getch(inode);
		}
		PIPE_SIZE(inode) -= chars;
		left -= chars;
		wake_up(&PIPE_WAIT(inode));
		if (inode->i_count < 2) {
			return size - left;
		}
		sleep_on(&PIPE_WAIT(inode));
	}
	wake_up(&PIPE_WAIT(inode));
	return size - left;
}

int write_pipe(struct inode *inode, char *buf, size_t size)
{
	int chars;
	int left = size;
	while (left) {
		chars = min(left,4096- PIPE_SIZE(inode));
		for (int i = chars; i > 0; i--) {
			pipe_putch(inode,*buf++);
		}
		PIPE_SIZE(inode) += chars;
		left -= chars;
		wake_up(&PIPE_WAIT(inode));
		if (inode->i_count < 2) {
			return size - left;
		}
		sleep_on(&PIPE_WAIT(inode));
	}
	wake_up(&PIPE_WAIT(inode));
	return size - left;
}

int pipe_open(struct inode *inode)
{
	PIPE_BUF(inode)=__va(get_page());
	PIPE_HEAD(inode)=0;
	PIPE_TAIL(inode)=0;
	PIPE_SIZE(inode)=0;
	PIPE_WAIT(inode)=0;
	return 0;
}

int pipe_close(struct inode *inode)
{
	put_page(__pa(PIPE_BUF(inode)));
	return 0;
}

int pipe_ioctl(struct inode *inode, int cmd, long arg)
{
	switch (cmd) {
		default:
			return 0;
	}
}

int sys_pipe(int res_fd[2])
{
	int fd[2];
	struct file *filp[2];
	struct task *current=CURRENT_TASK();
	struct inode *inode;
	int j=0;
	for(int i=0; j<2&& i<NR_FILE;i++)
		if(!file_table[i].f_count)
			filp[j++]=file_table+i;
	if(j<2)
		return -EAGAIN;
	j=0;
	for(int i=0; j<2 && i<NR_OPEN ;i++)
		if(!current->file[i])
			fd[j++]=i;
	if(j<2)
		return -EAGAIN;
	if(!(inode=iget(0,0)))
		return -EAGAIN;

	pipe_open(inode);
	inode->i_count++;
	iunlock(inode);

	filp[0]->f_count=filp[1]->f_count=1;
	filp[0]->f_inode=filp[1]->f_inode=inode;
	filp[0]->f_pos=filp[1]->f_pos=0;
	filp[0]->f_mode=O_READ ;
	filp[1]->f_mode=O_WRITE;

	current->file[fd[0]]=filp[0];
	current->file[fd[1]]=filp[1];

	res_fd[0]=fd[0];
	res_fd[1]=fd[1];
	return 0;
}
