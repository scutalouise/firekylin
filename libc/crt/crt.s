;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

extern main,exit
global _start,environ

section .text
_start:
	mov  ax,ss
	mov  ds,ax
	mov  es,ax
	mov  eax,[esp+8]
	mov  dword [environ],eax
	call main
	push eax
	call exit
	mov  eax,4
	int  0x30

section .data
environ:
	dd 0
