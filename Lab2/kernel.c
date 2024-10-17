#include "vga/vga.h"
#include "gdt/gdt.h"
#include <stdint.h>

extern void disable_interrupts(void);
extern void reload_segments(void);
extern void enter_protected_mode(void);
extern void leave_protected_mode(void);

tss_entry_t tss4, tss5, tss6;

void set_tss(tss_entry_t* tss, u32 eip, u32 esp) {
    tss->esp0 = esp;
    tss->ss0 = 0x10;
    tss->eip = eip;
    tss->esp = esp;
    tss->cs = 0x08;
    tss->ss = tss->ds = tss->es = tss->fs = tss->gs = 0x10;
    tss->iomap_base = sizeof(tss_entry_t);
}

void task1(void) {
    for (int i = 0; i < 2; i++) {
        print("Task 1 - Part ");
        print_int(i);
        print("\n");
        for (volatile int j = 0; j < 1000000; j++); // Пустой цикл
    }
    print("Task 1 completed\n");
}

void task2(void) {
    for (int i = 0; i < 2; i++) {
        print("Task 2 - Part ");
        print_int(i);
        print("\n");
        for (volatile int j = 0; j < 1000000; j++); // Пустой цикл
    }
    print("Task 2 completed\n");
}

void task3(void) {
    for (int i = 0; i < 2; i++) {
        print("Task 3 - Part ");
        print_int(i);
        print("\n");
        for (volatile int j = 0; j < 1000000; j++); // Пустой цикл
    }
    print("Task 3 completed\n");
}

void setup(void) {
    disable_interrupts();
    setupGdt();
    reload_segments();
    enter_protected_mode();
}

void leave(void) {
    disable_interrupts();
    print("Disabling interrupts\n");
    leave_protected_mode();
    print("Leaving protected mode\n");
}

void kmain(void) {
    clear();
    print("Welcome to the real mode!\n");
    setup();
    print("You're in a protected mode now\n");

    // Настройка TSS для задач
    set_tss(&tss4, (u32)task1, 0x9FC00);
    set_tss(&tss5, (u32)task2, 0x9F800);
    set_tss(&tss6, (u32)task3, 0x9F400);

    // Запуск задач
    asm volatile ("ltr %%ax" : : "a"(0x28)); // Загрузка TSS для task1
    asm volatile ("jmp $0x20, $0"); // Переход к task1

    leave();
    print("You're back in real mode\n");

    while (1) {
        // Бесконечный цикл для предотвращения завершения программы
    }
}