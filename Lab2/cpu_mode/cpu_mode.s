global disable_interrupts
global reload_segments
global enter_protected_mode
global leave_protected_mode

disable_interrupts:
    ; Disable maskable interrupts
    CLI
    ; Disable NMIs by setting bit 7 of port 0x70
    IN al, 0x70
    OR al, 0x80
    OUT 0x70, al
    IN al, 0x71
    RET

reload_segments:
    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    MOV ss, ax
    RET

enter_protected_mode:
    MOV eax, cr0
    OR eax, 0x1
    MOV cr0, eax
    JMP 0x08:.flush

.flush:
    RET

idt_real:
	DW 0x3ff		; 256 entries, 4b each = 1K
	DD 0			; Real Mode IVT @ 0x0000

leave_protected_mode:
    MOV eax, cr0
    AND eax, 0xFFFFFFFE
    MOV cr0, eax
    JMP 0x0:real_mode_entry

real_mode_entry:
    MOV ax, 0
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    MOV ss, ax

    LIDT [idt_real]

    ; Enable maskable interrupts
    STI
    ; Enable NMIs by clearing bit 7 of port 0x70
    IN al, 0x70
    AND al, 0x7F
    OUT 0x70, al
    IN al, 0x71
    RET