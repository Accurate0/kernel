; Multiboot header
; magic    - 0
; flags    - 4
; checksum - 8
extern init
MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
VIDMODE equ 1 << 2
FLAGS   equ MBALIGN | MEMINFO | VIDMODE
MAGIC   equ 0x1BADB002
CHKSUM  equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHKSUM

    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000

    dd 0x00000000
    dd 1280
    dd 1024
    dd 32

; create our stack
; must be aligned on 16 bit according to System V
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:


section .text
; fixed symbol size
global _start:function (_start.end - _start)
_start:
    ; turn off interrupts
    cli

    ; setup stack to call into C
    mov esp, stack_top
    push ebx

    call init
    ; shouldn't return but

.hang:	hlt
    jmp .hang
.end:
