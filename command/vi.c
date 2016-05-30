/*
 *    command/vi.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MODE_VIEW	1
#define MODE_INSERT	2
#define MODE_REPLACE	3

struct line_node{
	char  data[160];
	int   count;
	struct line_node *prev;
	struct line_node *next;
};

struct line_node *first;	/* first line of file */
struct line_node *start;	/* bengin to show */

int cur_x,cur_y;		/* cur in screen  */

struct line_node *cur_line;	/* current line of edit */
int cur_index;			/* current cur in line */

int read_char(int fd)
{
	char ch;

	if(read(fd,&ch,1)<0)
		return EOF;
	return ch;
}

struct line_node *new_line_node(void)
{
	struct line_node *res;

	res=(struct line_node *)malloc(sizeof(struct line_node));
	if(!res){
		printf("\0330;24POut Of Memory");
		// save file();
		exit(0);
	}
	return res;
}

void free_line_node(struct line_node *node)
{
	return free(node);
}

void load_file(int fd)
{
	struct line_node *prev=NULL;
	while(1){


	}
}

int main(int argc ,char **argv)
{
	int fd;
	char ch;
	int mode;

	if(argc <2 )
		fd=open("default.vi",O_RDWR,0);
	else
		fd=open(argv[1],O_RDWR,0);

	if(fd<0)
		exit(printf("file open error"));

	load_file(fd);

	draw_win();

	while(1){
		ch=read_char(0);
		switch(mode){
		case MODE_VIEW:
			switch(ch){
			case 'h':
				// left
				break;
			case 'k':
				// up
				break;
			case 'l':
				// right
				break;
			case 'j':
				// down
				break;
			case 'i':
				mode=MODE_INSERT;
				break;
			case 'r':
				mode=MODE_REPLACE;
				break;
			case 'w':
				// save
				break;
			case 'q':
				// save and quit
				break;
			case 'Q':
				// quit with no save
				break;
			default:
				continue;
			}
			break;

		case MODE_INSERT:
			if(ch=='\033'){
				mode=MODE_VIEW;
				continue;
			}
			else if(ch=='\b')
				nop();//del_char();
			else if (ch=='\n')
				nop(); //new_line()
			else
				nop(); //insert_char()
			break;
		case MODE_REPLACE:
			if(ch=='\033'){
				mode=MODE_VIEW;
				continue;
			}
			// repace char '\n' cannot be repace
		}
	}
}

void insert_char(struct line_node *line,char ch)
{
	for(int i=line->count;i<cur_index;i--)
		line->data[i+1]=line->data[i];
	line[cur_index++]=ch;
	if(ch!='\t')
		cur_x++;
	else
		cur_x=(cur_x+7)&~7;
	if(cur_x>79)
		cur_x=79;
	// update_line_srceen
}

void del_char(struct line_node *line)
{
	/* this will conact two line,buf if do this more ,it will out of buf */
	if(cur_index==0 ){
		struct line_node *tmp=line->prev;
		if(!tmp)
			return ;
		for(int i=0;i<line->count;i++)
			tmp->data[tmp->count++]=line->data[i];
		line->next->prev=tmp;
		tmp->next=line->next;
		cur_line=tmp;
		free_line_node(line);
		if(cur_y)
			cur_y--;
		// update_screen;
	}
	else{
		for(int i=cur_index;i<line->count;i++)
			line->data[i]=line->data[i+1];
		cur_index--;
		line->count--;
		// update_line_creen
	}
}

void new_line(struct line_node *line)
{
	struct line_node *new;

	new=new_line_node();

	for(int i=cur_index,j=0;i<line->count;i++)
		new->data[j++]=line->data[i];
	new->count=line->count-cur_index;
	line->data[cur_index]='\n';
	line->count=cur_index+1;
	new->next=line->next;
	new->prev=line;
	line->next->prev=new;
	line->next=new;
	cur_index=0;
	cur_line=new;
	// update screen
}
