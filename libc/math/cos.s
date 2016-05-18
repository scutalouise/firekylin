;/*
; *    libc/math/cos.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global cos

cos:
	fld  qword [esp+4]
	fcos
	ret
