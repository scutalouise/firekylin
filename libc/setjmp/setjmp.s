;/*
; *    libc/setjmp/setjmp.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

;/*
; * We need to save all regs except %eax,%ecx,%edx, as these are
; * used by calls.
; * Jump buffer looks like this (same as bruce evans for minix):
; *
; * 00: %ebp
; * 04: %esp
; * 08: %eip
; * 0C: %ebx
; * 10: %esi
; * 14: %edi
; */

section .text
global setjmp,longjmp

setjmp:
	pop ecx
	mov edx,[esp]
	mov [edx],ebp
	mov [edx+4],esp
	mov [edx+8],ecx
	mov [edx+12],ebx
	mov [edx+16],esi
	mov [edx+20],edi
	xor eax,eax
	jmp [ecx]

longjmp:
	mov edx,[esp+4]
	mov eax,[esp+8]
	cmp eax,1
	adc eax,0
	mov ebp,[edx]
	mov esp,[edx+4]
	mov ecx,[edx+8]
	mov ebx,[edx+12]
	mov esi,[edx+16]
	mov edi,[edx+20]
	jmp [ecx]
