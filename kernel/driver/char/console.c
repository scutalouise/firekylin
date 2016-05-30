/*
 *    driver/console.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <firekylin/kernel.h>
#include <firekylin/tty.h>

struct console {
	unsigned long base;
	unsigned long origin;
	unsigned char x;
	unsigned char y;
	unsigned char color;
};

struct console con_table[MAX_CON];

unsigned int fg_console;
unsigned int cur_console;

#define base	(con_table[cur_console].base)
#define origin	(con_table[cur_console].origin)
#define x	(con_table[cur_console].x)
#define y	(con_table[cur_console].y)
#define color	(con_table[cur_console].color)

int __echo__=1;

void con_init()
{
	for (int cur_console = 0; cur_console < MAX_CON; cur_console++) {
		origin = base = 0xc00b8000 + 25 * 80 * 2 * cur_console;
		x = y = 0;
		color = 15;
	}
}

void srcup()
{
	if (y < 25)
		return;
	memcpy((char*) base, (char*) base + 160, 80 * 24 * 2);
	memset((char*) base + 80 * 24 * 2, 0, 80 * 2);
	y = 24;
}

void write_char(char ch)
{
	char *p = (char*)( base + (y * 80 + x) * 2);
	if (ch == '\r')
		return;
	if (ch == '\b' && x > 0) {
		*--p = color;
		*--p = ' ';
		x--;
	} else if (ch == '\t') {
		do {
			*p++ = ' ';
			*p++ = color;
		} while (++x % 8);
	} else if (ch == '\n') {
		y++;
		x = 0;
		srcup();
	} else {
		*p++ = ch;
		*p++ = color;
		x++;
		if (x >= 80) {
			x = 0;
			y++;
			srcup();
		}
	}
}

void set_orign(void)
{
	outb(0x3d4, 12);
	outb(0x3d5, (base-0xc00b8000)>>9 & 0xff);
	outb(0x3d4, 13);
	outb(0x3d5, (base-0xc00b8000)>>1 & 0xff);
}

void set_cur(void)
{
	outb(0x3d4, 14);
	outb(0x3d5, ((base + (y * 80 + x)*2 -0xc00b8000) >> 9) & 0xff);
	outb(0x3d4, 15);
	outb(0x3d5, (base + (y * 80 + x)*2 -0xc00b8000)>>1 & 0xff);
}

int con_write(struct tty_struct *tty)
{
	char ch;
	int res = 0;
	cur_console = tty-tty_table-1;
	irq_lock();
	while (!isempty(tty->out)) {
		GETCH(tty->out, ch);
		if (ch == '\033') {
			char tmp_x = 0, tmp_y = 0;
			while (1) {
				GETCH(tty->out, ch);
				if (ch >= '0' && ch <= '9')
					tmp_x = tmp_x * 10 + ch - '0';
				else
					break;
			}
			if (ch == ';') {
				while (1) {
					GETCH(tty->out, ch);
					if (ch >= '0' && ch <= '9')
						tmp_y = tmp_y * 10 + ch - '0';
					else
						break;
				}
			}
			if (ch == 'P') {
				if (tmp_x >= 80)
					x = 79;
				else
					x = tmp_x;
				if (tmp_y >= 25)
					x = 24;
				else
					y = tmp_y;
			} else if (ch == 'C')
				color = ((tmp_x << 4) & 0xf0) | (tmp_y & 0xf);
			else if (ch=='E')
				__echo__=0;
			else if (ch=='e')
				__echo__=1;
		} else
			write_char(ch);
		res++;
	}
	if (fg_console == cur_console)
		set_cur();
	irq_unlock();
	return res;
}

void select_con(int con)
{
	if(fg_console==con)
		return ;
	fg_console=con;
	cur_console=con;
	set_orign();
	set_cur();
}
