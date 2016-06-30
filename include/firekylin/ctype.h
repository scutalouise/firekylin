/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _CTYPE_H
#define _CTYPE_H

#define _U	0x01	/* upper        */
#define _L	0x02	/* lower        */
#define _D	0x04	/* digit        */
#define _C	0x08	/* control      */
#define _P	0x10	/* punct        */
#define _S	0x20	/* white space  */
#define _X	0x40	/* hex digit    */

extern unsigned char __ctype[];

#define isupper(c)	(__ctype[(c)+1]&(_U))
#define islower(c)	(__ctype[(c)+1]&(_L))
#define isdigit(c)	(__ctype[(c)+1]&(_D))
#define iscntrl(c)	(__ctype[(c)+1]&(_C))
#define isspace(c)	(__ctype[(c)+1]&(_S))
#define ispunct(c)	(__ctype[(c)+1]&(_P))
#define isxdigit(c)	(__ctype[(c)+1]&(_D|_X))
#define isalpha(c)	(__ctype[(c)+1]&(_U|_L))
#define isalnum(c)	(__ctype[(c)+1]&(_U|_L|_D))
#define isgraph(c)	(__ctype[(c)+1]&(_P|_U|_L|_D))
#define isprint(c)	(__ctype[(c)+1]&(_P|_U|_L|_D))

#define tolower(c)	(isupper(c) ? (c)+0x20 : (c))
#define toupper(c)	(islower(c) ? (c)-0x20 : (c))

#endif
