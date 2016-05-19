;/*
; *    libc/math/fmod.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

global fmod

fmod:
	fld  qword [esp+12]
	fld  qword [esp+4]
loop:
	fprem1
	fstsw ax
	sahf
	jpe loop
	fstp st1
	ret
