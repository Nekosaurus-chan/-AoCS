; Disassembly of file: test.o
; Sun Mar 24 14:59:17 2024
; Type: ELF64
; Syntax: NASM
; Instruction set: SSE2, x64

default rel

global Y: function
global factorial: function
global S: function

extern pow                                              ; near
extern sin                                              ; near


SECTION .text   align=1 exec                            ; section number 1, code

Y:      ; Function begin
        endbr64                                         ; 0000 _ F3: 0F 1E. FA
        push    rbp                                     ; 0004 _ 55
        mov     rbp, rsp                                ; 0005 _ 48: 89. E5
        sub     rsp, 16                                 ; 0008 _ 48: 83. EC, 10
        movss   dword [rbp-4H], xmm0                    ; 000C _ F3: 0F 11. 45, FC
        pxor    xmm1, xmm1                              ; 0011 _ 66: 0F EF. C9
        cvtss2sd xmm1, dword [rbp-4H]                   ; 0015 _ F3: 0F 5A. 4D, FC
        movq    rax, xmm1                               ; 001A _ 66 48: 0F 7E. C8
        movq    xmm0, rax                               ; 001F _ 66 48: 0F 6E. C0
        call    sin                                     ; 0024 _ E8, 00000000(PLT r)
        cvtsd2ss xmm0, xmm0                             ; 0029 _ F2: 0F 5A. C0
        leave                                           ; 002D _ C9
        ret                                             ; 002E _ C3
; Y End of function

factorial:; Function begin
        endbr64                                         ; 002F _ F3: 0F 1E. FA
        push    rbp                                     ; 0033 _ 55
        mov     rbp, rsp                                ; 0034 _ 48: 89. E5
        mov     dword [rbp-14H], edi                    ; 0037 _ 89. 7D, EC
        mov     dword [rbp-8H], 1                       ; 003A _ C7. 45, F8, 00000001
        mov     dword [rbp-4H], 1                       ; 0041 _ C7. 45, FC, 00000001
        jmp     ?_002                                   ; 0048 _ EB, 0E

?_001:  mov     eax, dword [rbp-8H]                     ; 004A _ 8B. 45, F8
        imul    eax, dword [rbp-4H]                     ; 004D _ 0F AF. 45, FC
        mov     dword [rbp-8H], eax                     ; 0051 _ 89. 45, F8
        add     dword [rbp-4H], 1                       ; 0054 _ 83. 45, FC, 01
?_002:  mov     eax, dword [rbp-4H]                     ; 0058 _ 8B. 45, FC
        cmp     eax, dword [rbp-14H]                    ; 005B _ 3B. 45, EC
        jle     ?_001                                   ; 005E _ 7E, EA
        mov     eax, dword [rbp-8H]                     ; 0060 _ 8B. 45, F8
        pop     rbp                                     ; 0063 _ 5D
        ret                                             ; 0064 _ C3
; factorial End of function

S:      ; Function begin
        endbr64                                         ; 0065 _ F3: 0F 1E. FA
        push    rbp                                     ; 0069 _ 55
        mov     rbp, rsp                                ; 006A _ 48: 89. E5
        sub     rsp, 32                                 ; 006D _ 48: 83. EC, 20
        movss   dword [rbp-14H], xmm0                   ; 0071 _ F3: 0F 11. 45, EC
        mov     dword [rbp-18H], edi                    ; 0076 _ 89. 7D, E8
        pxor    xmm0, xmm0                              ; 0079 _ 66: 0F EF. C0
        movss   dword [rbp-8H], xmm0                    ; 007D _ F3: 0F 11. 45, F8
        mov     dword [rbp-4H], 0                       ; 0082 _ C7. 45, FC, 00000000
        jmp     ?_004                                   ; 0089 _ E9, 00000097

?_003:  pxor    xmm0, xmm0                              ; 008E _ 66: 0F EF. C0
        cvtsi2sd xmm0, dword [rbp-4H]                   ; 0092 _ F2: 0F 2A. 45, FC
        mov     rax, qword [rel ?_005]                  ; 0097 _ 48: 8B. 05, 00000000(rel)
        movapd  xmm1, xmm0                              ; 009E _ 66: 0F 28. C8
        movq    xmm0, rax                               ; 00A2 _ 66 48: 0F 6E. C0
        call    pow                                     ; 00A7 _ E8, 00000000(PLT r)
        movsd   qword [rbp-20H], xmm0                   ; 00AC _ F2: 0F 11. 45, E0
        mov     eax, dword [rbp-4H]                     ; 00B1 _ 8B. 45, FC
        add     eax, eax                                ; 00B4 _ 01. C0
        add     eax, 1                                  ; 00B6 _ 83. C0, 01
        pxor    xmm0, xmm0                              ; 00B9 _ 66: 0F EF. C0
        cvtsi2sd xmm0, eax                              ; 00BD _ F2: 0F 2A. C0
        pxor    xmm3, xmm3                              ; 00C1 _ 66: 0F EF. DB
        cvtss2sd xmm3, dword [rbp-14H]                  ; 00C5 _ F3: 0F 5A. 5D, EC
        movq    rax, xmm3                               ; 00CA _ 66 48: 0F 7E. D8
        movapd  xmm1, xmm0                              ; 00CF _ 66: 0F 28. C8
        movq    xmm0, rax                               ; 00D3 _ 66 48: 0F 6E. C0
        call    pow                                     ; 00D8 _ E8, 00000000(PLT r)
        movapd  xmm2, xmm0                              ; 00DD _ 66: 0F 28. D0
        mulsd   xmm2, qword [rbp-20H]                   ; 00E1 _ F2: 0F 59. 55, E0
        movsd   qword [rbp-20H], xmm2                   ; 00E6 _ F2: 0F 11. 55, E0
        mov     eax, dword [rbp-4H]                     ; 00EB _ 8B. 45, FC
        add     eax, eax                                ; 00EE _ 01. C0
        add     eax, 1                                  ; 00F0 _ 83. C0, 01
        mov     edi, eax                                ; 00F3 _ 89. C7
        call    factorial                               ; 00F5 _ E8, 00000000(PLT r)
        pxor    xmm0, xmm0                              ; 00FA _ 66: 0F EF. C0
        cvtsi2sd xmm0, eax                              ; 00FE _ F2: 0F 2A. C0
        movsd   xmm1, qword [rbp-20H]                   ; 0102 _ F2: 0F 10. 4D, E0
        divsd   xmm1, xmm0                              ; 0107 _ F2: 0F 5E. C8
        pxor    xmm0, xmm0                              ; 010B _ 66: 0F EF. C0
        cvtss2sd xmm0, dword [rbp-8H]                   ; 010F _ F3: 0F 5A. 45, F8
        addsd   xmm0, xmm1                              ; 0114 _ F2: 0F 58. C1
        cvtsd2ss xmm0, xmm0                             ; 0118 _ F2: 0F 5A. C0
        movss   dword [rbp-8H], xmm0                    ; 011C _ F3: 0F 11. 45, F8
        add     dword [rbp-4H], 1                       ; 0121 _ 83. 45, FC, 01
?_004:  mov     eax, dword [rbp-4H]                     ; 0125 _ 8B. 45, FC
        cmp     eax, dword [rbp-18H]                    ; 0128 _ 3B. 45, E8
        jle     ?_003                                   ; 012B _ 0F 8E, FFFFFF5D
        movss   xmm0, dword [rbp-8H]                    ; 0131 _ F3: 0F 10. 45, F8
        leave                                           ; 0136 _ C9
        ret                                             ; 0137 _ C3
; S End of function


SECTION .data   align=1 noexec                          ; section number 2, data


SECTION .bss    align=1 noexec                          ; section number 3, bss


SECTION .rodata align=8 noexec                          ; section number 4, const

?_005:                                                  ; qword
        dq 0BFF0000000000000H                           ; 0000 _ BFF0000000000000 


SECTION .note.gnu.property align=8 noexec               ; section number 5, const

        db 04H, 00H, 00H, 00H, 10H, 00H, 00H, 00H       ; 0000 _ ........
        db 05H, 00H, 00H, 00H, 47H, 4EH, 55H, 00H       ; 0008 _ ....GNU.
        db 02H, 00H, 00H, 0C0H, 04H, 00H, 00H, 00H      ; 0010 _ ........
        db 03H, 00H, 00H, 00H, 00H, 00H, 00H, 00H       ; 0018 _ ........


