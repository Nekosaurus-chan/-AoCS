global load_gdt

load_gdt:
    ; Load the GDT
    MOV eax, [esp + 4]
    LGDT [eax]
    RET