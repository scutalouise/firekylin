/*
 *    include/stdio.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/types.h>
#include <stddef.h>

typedef struct __iobuf {
	int		_count;
	int		_fd;
	int		_flags;
	int		_bufsiz;
	unsigned char	*_buf;
	unsigned char	*_ptr;
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

/* The following definitions are also in <unistd.h>. They should not
 * conflict.
 */
#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define	BUFSIZ		4096
#define	EOF		(-1)

#define	FOPEN_MAX	20

#define	FILENAME_MAX	NAME_MAX

typedef long int	fpos_t;

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

extern FILE * fopen(char *name, const char *mode);
extern FILE * fdopen(int fd, const char *mode);
extern FILE * freopen(FILE *stream, char *name, const char *mode);
extern int    fclose(FILE *stream);
extern int    fflush(FILE *stream);
extern int    fgetc(FILE *stream);
extern char * fgets(FILE *stream, char *s, size_t n);
extern int    fputc(FILE *stream, int c);
extern int    fputs(FILE *stream, char *s);
extern size_t fread(FILE *stream, void *ptr, size_t size, int count);
extern size_t fwrite(FILE *stream, void *ptr, size_t size, int count);
extern int    fseek(FILE *stream, off_t offset, int whence);
extern off_t  ftell(FILE *stream);
extern void   frewind(FILE *stream);
extern void   setbuf(FILE *stream, char *buf);
extern int    setvbuf(FILE *stream, char *buf, int mode, size_t size);
extern int    fgetpos(FILE *stream, fpos_t *pos);
extern int    fsetpos(FILE *stream, fpos_t *pos);
extern int    ungetc(FILE *stream, int ch);
extern int    fileno(FILE *stream);
extern int    ferror(FILE *stream);
extern void   fclearerr(FILE *stream);
extern int    feof(FILE *stream);

extern int    printf(char *fmt, ...);
extern int    sprintf(char *buf, char*fmt, ...);
extern int    fprintf(FILE *stream, char *buf, ...);

//int myprintf(char *fmt, ...);
//#define printf  myprintf

#define fileno(p)	((p)->_fd)
#define	feof(p)		(((p)->_flags & _IOEOF) != 0)
#define	ferror(p)	(((p)->_flags & _IOERR) != 0)
#define clearerr(p)     ((p)->_flags &= ~(_IOERR|_IOEOF))

#define getchar()	fgetc(stdin)
#define putchar(c)	fputc(stdout,c)
#define puts(s)		fputs(stdout,s)

#endif
