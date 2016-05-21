;/*
; *    libc/math/lg.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */


; log (base 10) m=log (base 10) 2 * log (base 2) m

global lg

lg:
	fldlg2			; st0=log (base 10) 2
	fld  qword [esp+4]
	fyl2x			; st0=st1 *log (base 2) st0
	ret
