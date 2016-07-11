;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global  div_zero, debug, nmi, breakpoint, overflow, bound,invalid_opcode
global  device_not_invalid,double_fault,coprocessor_overrun,invalid_tss
global  segment_not_exsit,stack,general_protection,page_fault
global  reserved,coprocessor,align_check,machine_check,simd_float
global  hwint0,hwint1,hwint2,hwint3,hwint4,hwint5,hwint6,hwint7
global  hwint8,hwint9,hwintA,hwintB,hwintC,hwintD,hwintE,hwintF
global  syscall

extern  execption, do_signal
extern	sys_fork,   sys_exec,   sys_sbrk,    sys_wait,    sys_exit
extern 	sys_trace,  sys_alarm,  sys_sigctl,  sys_getpid,  sys_setgrp
extern  sys_setsid, sys_getuid, sys_setuid,  sys_getgid,  sys_setgid
extern  sys_access, sys_open,   sys_read,    sys_write,   sys_close
extern  sys_lseek,  sys_fcntl,  sys_ioctl,   sys_pipe,    sys_mknod
extern  sys_mkdir,  sys_link,   sys_rename,  sys_unlink,  sys_rmdir
extern  sys_chdir,  sys_mount,  sys_umount,  sys_stat,    sys_fstat
extern  sys_chmod,  sys_chown,  sys_utime,   sys_sync,    sys_getime
extern  sys_setime, sys_sigsend, sys_sigmask, sys_sigact, sys_times

syscall_table:
    dd  sys_fork,   sys_exec,   sys_sbrk,    sys_wait,    sys_exit
    dd  sys_trace,  sys_alarm,  sys_sigctl,  sys_getpid,  sys_setgrp
    dd  sys_setsid, sys_getuid, sys_setuid,  sys_getgid,  sys_setgid
    dd  sys_access, sys_open,   sys_read,    sys_write,   sys_close
    dd  sys_lseek,  sys_fcntl,  sys_ioctl,   sys_pipe,    sys_mknod
    dd  sys_mkdir,  sys_link,   sys_rename,  sys_unlink,  sys_rmdir
    dd  sys_chdir,  sys_mount,  sys_umount,  sys_stat,    sys_fstat
    dd  sys_chmod,  sys_chown,  sys_utime,   sys_sync,    sys_getime
    dd  sys_setime, sys_sigsend, sys_sigmask, sys_sigact, sys_times

div_zero:
	push 0
	push 0
	jmp  _execption
debug:
	push 0
	push 1
	jmp  _execption
nmi:
	push 0
	push 2
	jmp  _execption
breakpoint:
	push 0
	push 3
	jmp  _execption
overflow:
	push 0
	push 4
	jmp  _execption
bound:
	push 0
	push 5
	jmp  _execption
invalid_opcode:
	push 0
	push 6
	jmp  _execption
device_not_invalid:
	push 0
	push 7
	jmp  _execption
double_fault:
	push 8
	jmp  _execption
coprocessor_overrun:
	push 0
	push 9
	jmp  _execption
invalid_tss:
	push 10
	jmp  _execption
segment_not_exsit:
	push 11
	jmp  _execption
stack:
	push 12
	jmp  _execption
general_protection:
	push 13
	jmp  _execption
page_fault:
	push 14
	jmp  _execption
reserved:
	push 0
	push 15
	jmp  _execption
coprocessor:
	push 0
	push 16
	jmp  _execption
align_check:
	push 17
	jmp  _execption
machine_check:
	push 0
	push 18
	jmp  _execption
simd_float:
	push 0
	push 19
	jmp  _execption
hwint0:
	push 0
	push 0x20
	jmp  _execption
hwint1:
	push 0
	push 0x21
	jmp  _execption
hwint2:
	push 0
	push 0x22
	jmp  _execption
hwint3:
	push 0
	push 0x23
	jmp  _execption
hwint4:
	push 0
	push 0x24
	jmp  _execption
hwint5:
	push 0
	push 0x25
	jmp  _execption
hwint6:
	push 0
	push 0x26
	jmp  _execption
hwint7:
	push 0
	push 0x27
	jmp  _execption
hwint8:
	push 0
	push 0x28
	jmp  _execption
hwint9:
	push 0
	push 0x29
	jmp  _execption
hwintA:
	push 0
	push 0x2a
	jmp  _execption
hwintB:
	push 0
	push 0x2b
	jmp  _execption
hwintC:
	push 0
	push 0x2c
	jmp  _execption
hwintD:
	push 0
	push 0x2d
	jmp  _execption
hwintE:
	push 0
	push 0x2e
	jmp  _execption
hwintF:
	push 0
	push 0x2f
_execption:
	push es
	push ds
	push ebp
	push esi
	push edi
	push edx
	push ecx
	push ebx
	push eax
	mov  ax,0x10
	mov  ds,ax
	mov  es,ax
	call execption
	jmp  _syscall_return

syscall:
	sub  esp,8
	push es
	push ds
	push ebp
	push esi
	push edi
	push edx
	push ecx
	push ebx
	mov  ebx,0x10
	mov  ds,bx
	mov  es,bx
	sti
	call [syscall_table+4*eax]
	push eax
_syscall_return:
	call do_signal
	cli
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop edi
	pop esi
	pop ebp
	pop ds
	pop es
	add esp,8
	iret
