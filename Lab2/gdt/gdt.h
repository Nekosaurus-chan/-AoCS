#include "../lib/stdint.h"

#define GDT_STD_SELECTOR_NULL       0
#define GDT_STD_SELECTOR_KERNEL_CS  1
#define GDT_STD_SELECTOR_KERNEL_DS  2
#define GDT_STD_SELECTOR_USR_CS     3
#define GDT_STD_SELECTOR_USR_DS     4

struct gdt_entry
{
    u16 limit_low;
    u16 base_low; 
    u8 base_middle; 
    u8 access; 
    u8 flags;
    u8 base_high; 
} __attribute__((packed));

struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

typedef struct {
    u32 prev_tss;
    u32 esp0;
    u32 ss0;
    u32 esp1;
    u32 ss1;
    u32 esp2;
    u32 ss2;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es;
    u32 cs;
    u32 ss;
    u32 ds;
    u32 fs;
    u32 gs;
    u32 ldt;
    u16 trap;
    u16 iomap_base;
} __attribute__((packed)) tss_entry_t;

void setupGdt();
void destroyGdt();
void setGdtEntry(u32 id, u32 base, u32 limit, u8 access, u8 flags);

#define GDT_NULL_CS     (GDT_STD_SELECTOR_NULL * sizeof(struct gdt_entry))
#define GDT_KERNEL_CS   (GDT_STD_SELECTOR_KERNEL_CS * sizeof(struct gdt_entry))
#define GDT_KERNEL_DS   (GDT_STD_SELECTOR_KERNEL_DS * sizeof(struct gdt_entry))
#define GDT_USR_CS      (GDT_STD_SELECTOR_USR_CS * sizeof(struct gdt_entry))
#define GDT_USR_DS      (GDT_STD_SELECTOR_USR_DS * sizeof(struct gdt_entry))

