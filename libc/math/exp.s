;/*
; *    libc/math/exp.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

; e^x=2^(x*log(base 2) e)

global exp

exp:
	fld    qword [esp+4]
	fldl2e			; st0=log(base 2) e
	fmulp
	f2xm1			; st0=st0*2^st1-1
	fld1
	faddp st1,st0
	ret
