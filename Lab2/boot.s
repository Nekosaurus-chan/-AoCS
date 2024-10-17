BITS 32

section .text
    ALIGN 4
    DD 0x1BADB002
    DD 0x00000000
    DD - (0x1BADB002 + 0x00000000)

global _start
extern kmain

_start:
    CLI
    MOV esp, stack
    CALL kmain
    HLT

section .bss
RESB 8192
stack: 