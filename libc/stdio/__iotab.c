
#include "stdio_loc.h"

static struct __iobuf __stdin = {
	0, 0, _IOREAD, 0,
	(unsigned char *)NULL, (unsigned char *)NULL, 
};

static struct __iobuf __stdout = {
	0, 1, _IOWRITE, 0,
	(unsigned char *)NULL, (unsigned char *)NULL, 
};

static struct __iobuf __stderr = {
	0, 2, _IOWRITE | _IOLBF, 0,
	(unsigned char *)NULL, (unsigned char *)NULL, 
};

FILE *__iotab[FOPEN_MAX] = {
	&__stdin,
	&__stdout,
	&__stderr,
	0
};

FILE *stdin=&__stdin;
FILE *stdout=&__stdout;
FILE *stderr=&__stderr;
