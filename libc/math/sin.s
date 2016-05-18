;/*
; *    libc/math/sin.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global sin

sin:
	fld  qword [esp+4]
	fsin
	ret
