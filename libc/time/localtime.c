/*
 *	libc/time/time.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <time.h>

struct tm *localtime(const time_t * t)
{
        time_t offset= *t;  /* seconds between local time and GMT */

	//if (timezone == -1) tzset();
       // offset = *t - timezone;

	//if (stm == (struct tm *)NULL) return stm; /* check for illegal time */
        //stm->tm_isdst = (dst == -1) ? -1 : 0;
        return  gmtime(&offset);;
}
