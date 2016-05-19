;/*
; *    libc/math/pow.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

; x^y=2^(y*log(base 2) x)

global pow

pow:
	fld    qword [esp+12]
	fld    qword [esp+4]
	fyl2x			; st0=st1*log(base 2) st0
	f2xm1			; st0=st0*2^st1-1
	fld1
	faddp st1,st0
	ret
