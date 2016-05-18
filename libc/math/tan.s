;/*
; *    libc/math/tan.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global tan

tan:
	fld  qword [esp+4]
	fptan
	fstp st0
	ret
