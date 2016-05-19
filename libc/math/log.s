;/*
; *    libc/math/log.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */


; log (base e) m=log (base e) 2 * log (base 2) m

global log

log:
	fldln2			; st0=log (base e) 2
	fld  qword [esp+4]
	fyl2x			; st0=st1 *log (base 2) st0
	ret
