/*
 *    include/stdio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

typedef struct _iobuf {
	int   _fd;
	int   _cnt;
	int   _bufsiz;
	int   _flag;
	char *_buf;
	char *_ptr;
} FILE;

#define	_IOFBF		0x000
#define	_IOREAD		0x001
#define	_IOWRITE	0x002
#define	_IONBF		0x004
#define	_IOMYBUF	0x008
#define	_IOEOF		0x010
#define	_IOERR		0x020
#define	_IOLBF		0x040
#define	_IOREADING	0x080
#define	_IOWRITING	0x100
#define	_IOAPPEND	0x200
#define _IOFIFO		0x400

/* The following definitions are also in <sys/unistd.h>.
 * They should not conflict.
 */
#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define	BUFSIZ		4096
#define	EOF		(-1)

#define	FOPEN_MAX	32

#define	FILENAME_MAX	NAME_MAX

#define	TMP_MAX		999

typedef long int	fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int myprintf(char *fmt,...);
#define printf  myprintf

extern int fileno(FILE *iop);
extern int __fillbuf(FILE *iop);
extern int __flushbuf(int c, FILE * iop);
extern FILE * fopen(char *name, char *mode);
extern int fclose(FILE *fp);
extern int fflush(FILE *iop);
extern int fgetc(FILE *iop);
extern int fgetpos(FILE *fp, fpos_t *pos);
extern char * fgets(char *s, size_t n, FILE *iop);
extern int fputc(int c,FILE *iop);
extern int fputs(const char *s, FILE *iop);
extern int fread(void *ptr, size_t size, int count, FILE *iop);
extern int fseek(FILE *iop, off_t offset, int whence);
extern int fsetpos(FILE *iop, fpos_t *pos);
extern long ftell(FILE *iop);
extern int fwrite(void *ptr, size_t size, int count, FILE * iop);
extern void rewind(FILE *iop);
extern void setbuf(FILE *iop, char *buf);
extern int setvbuf(FILE *iop, char *buf, int mode, size_t size);
extern int ungetc(int ch, FILE *iop);

#define	getc(p)		(--(p)->_cnt >= 0 ? \
		          (int) (*(p)->_ptr++) : __fillbuf(p))
#define	putc(c, p)	(--(p)->_cnt >= 0 ? \
			  (int) (*(p)->_ptr++ = (c)) :  __flushbuf((c),(p)))

#define getchar()	getc(stdin)
#define putchar()	putc(c,stdout)

#define	feof(p)		(((p)->_flag & _IOEOF) != 0)
#define	ferror(p)	(((p)->_flag & _IOERR) != 0)
#define clearerr(p)     ((p)->_flag &= ~(_IOERR|_IOEOF))

#endif
