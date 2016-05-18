;/*
; *    libc/math/sqrt.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global sqrt

sqrt:
	fld  qword [esp+4]
	fsqrt
	ret
