;/*
; *    libc/math/atan.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global atan

atan:
	fld  qword [esp+4]
	fld1
	fpatan
	ret
