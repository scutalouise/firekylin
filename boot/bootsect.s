;/*
; *    boot/bootsect.s
; *
; *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
; */

	bits 16
start:
	mov  ax,0x800
	mov  ds,ax
	mov  es,ax
	mov  ss,ax
	mov  sp,0x2000
	xor  di,di
	call read_block
	jmp  0x800:disp_load

disp_load:
	mov  cx,10
	mov  di,info
	mov  ah,0x0e
	mov  bx,0x10
.next:
	mov  al,[di]
	int  0x10
	inc  di
	loop .next
	
load_kernel:
	mov  ax,0x1000
	mov  es,ax
	mov  si,512
.loop:
	xor  di,di
	mov  bx,[si]
	cmp  bx,0
	je   .ok_load
	shl  bx,1
	call read_block
	mov  ah,0x0e	; echo .
	mov  bx,0x10
	mov  al,'.'
	int  0x10
	mov  ax,es
	add  ax,0x40
	mov  es,ax
	add  si,2
	jmp  .loop
	
.ok_load:
clear_screen:
	mov ax,0x0600
	xor cx,cx
	mov dh,24
	mov al,79
	mov bh,0x07
	int 0x10

get_mem:
	mov ah,0x88
	int 0x15
	mov word [0],ax ;0x8000


open_A20:
	cli
	in  al,  0x92
	or  al,  2
	out 0x92, al
	lgdt [gdt_48]
	mov eax, cr0
	or  eax, 1
	mov cr0, eax
	jmp dword 8:0x10000

;/*
; * read_block:start bx,number,2 addr es:di
; */
read_block:
	mov  dx,0x1f7
	in   al,dx
	and  al,0xC0
	cmp  al,0x40
	jne  read_block
	mov  dx,0x1f2
	mov  al,2
	out  dx,al	;outb(0x1f2,nr)
	inc  dx
	mov  al,bl
	out  dx,al	;outb(0x1f3,arg0)
	inc  dx
	mov  al,bh
	out  dx,al	;outb(0x1f4,arg1)
	inc  dx
	mov  al,0
	out  dx,al	;outb(0x1f5,arg2(0))
	inc  dx
	mov  al,0xe0
	out  dx,al	;outb(0x1f6,arg3(0xe0))
	inc  dx
	mov  al,0x20
	out  dx,al	;outb(0x1f7,cmd(read=0x20))
.wait1:
	in   al,dx
	and  al,0xC0
	cmp  al,0x40
	jne  .wait1
	mov  cx,256
	mov  dx,0x1f0
	rep  insw
.wait2:
	mov  dx,0x1f7
	in   al,dx
	and  al,0xC0
	cmp  al,0x40
	jne  .wait2
	mov  cx,256
	mov  dx,0x1f0
	rep  insw
	ret

info:
	db "Loading..."
	align 8
gdt:
	dd 0,0
	dd 0x0000ffff,0x00cf9a00
	dd 0x0000ffff,0x00cf9200
	dd 0x0000ffff,0x00cbfa00
	dd 0x0000ffff,0x00cbf200
gdt_48:
	dw 0x100-1
	dd gdt+0x8000

	times 510-($-$$) db 0
	dw  0xaa55
