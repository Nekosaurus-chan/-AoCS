#include "gdt.h"

extern void load_gdt(u32);

struct gdt_entry gdt[6];
struct gdt_ptr gp;

tss_entry_t tss1;

void setGdtEntry(u32 id, u32 base, u32 limit, u8 access, u8 flags)
{
    gdt[id].base_low = (base & 0xFFFF);
    gdt[id].base_middle = (base >> 16) & 0xFF;
    gdt[id].base_high = (base >> 24) & 0xFF;

    gdt[id].limit_low = (limit & 0xFFFF);
    gdt[id].flags = (limit >> 16) & 0x0F;

    gdt[id].flags |= (flags & 0xF0);
    gdt[id].access = access;
}

void setupGdt()
{
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base = (u32)&gdt;

    setGdtEntry(GDT_STD_SELECTOR_NULL, 0, 0, 0, 0); // Null segment
    setGdtEntry(GDT_STD_SELECTOR_KERNEL_CS, 0, 0xFFFFFFFF, 0x9A, 0xCF); // System code segment
    setGdtEntry(GDT_STD_SELECTOR_KERNEL_DS, 0, 0xFFFFFFFF, 0x92, 0xCF); // System data segment
    setGdtEntry(GDT_STD_SELECTOR_USR_CS, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    setGdtEntry(GDT_STD_SELECTOR_USR_DS, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    setGdtEntry(5, (u32)&tss1, sizeof(tss1), 0x89, 0x40); // TSS
    load_gdt((u32)&gp);
}