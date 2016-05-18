;/*
; *    libc/math/sqrt.s
; *
; *    (C) 2016 ximo<ximoos@foxmail.com> port form newlibc
; */

global floor

floor:
	push ebp
	mov  ebp,esp
	sub  esp,8
	fstcw [ebp-4]  ;  -4 =old CW -2 =new CW
	fwait
	mov  ax,[ebp-4]
	and  ax,0xf3ff
	or   ax,0x0400
	mov  [ebp-2],ax
	fldcw[ebp-2]
	fld  qword [ebp+8]
	frndint
	fldcw [ebp-4]
	leave
	ret
