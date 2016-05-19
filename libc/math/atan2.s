;/*
; *    libc/math/atan2.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global atan2

atan2:
	fld  qword [esp+4]
	fld  qword [esp+12]
	fpatan
	ret
