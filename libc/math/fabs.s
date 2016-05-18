;/*
; *    libc/math/fabs.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global fabs

fabs:
	fld  qword [esp+4]
	fabs
	ret
