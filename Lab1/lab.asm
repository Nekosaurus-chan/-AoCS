[BITS 16]
[ORG 0x7C00]

start:
    cli                  
    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    lgdt [gdt_descriptor] ;prepare table -> block interrupt -> remember segment ans sp -> load GDTR com LGDT 

    mov eax, cr0  ; PE CR0 -> 1
    or eax, 1
    mov cr0, eax
    jmp CODE_SEL:protected_mode_entry ; clear proc -> call gdt -> choose desc and load cs -> choosing coms

[BITS 32]
protected_mode_entry:

    mov ax, DATA_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Clear screen
    mov edi, 0xB8000
    ; Space with black background, white foreground
    mov ax, 0x0720
    mov ecx, 80*25        
    rep stosw

    mov edi, 0xB8000
    mov esi, msg
    call print_string

    cli
    mov eax, cr0
    and eax, 0xFFFFFFFE
    mov cr0, eax

    jmp 0x0000:real_mode_entry

[BITS 16]
real_mode_entry:
    hlt
    jmp $

print_string:
    lodsb
    test al, al
    jz .done
    ; Attribute: white on black
    mov ah, 0x07
    stosw
    jmp print_string
.done:
    ret

msg db 'Message in protected mode!', 0

align 8
gdt:
    dq 0x0000000000000000 ; 
    dq 0x00CF9A000000FFFF ; Code
    dq 0x00CF92000000FFFF ; Data

gdt_descriptor:
    dw gdt_end - gdt - 1
    dd gdt

gdt_end:

CODE_SEL equ 0x08
DATA_SEL equ 0x10

times 510-($-$$) db 0
; Boot sector signature
dw 0xAA55