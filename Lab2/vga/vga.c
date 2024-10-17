#include "vga.h"

u16 column = 0;
u16 row = 0;
u16* const vga_buffer = (u16* const)0xB8000;
const u16 defaultColor = (COLOR_LIGHT_GREY << 8) | (COLOR_BLACK << 12);
u16 currentColor = defaultColor;

void clear()
{
    row = 0;
    column = 0;
    currentColor = defaultColor;

    for (u16 y = 0; y < VGA_HEIGHT; y++)
    {
        for (u16 x = 0; x < VGA_WIDTH; x++)
        {
            const u16 index = y * VGA_WIDTH + x;
            vga_buffer[index] = ' ' | defaultColor;
        }
    }
}

void newline()
{
    if (row < VGA_HEIGHT - 1)
    {
        row++;
        column = 0;
    } else
    {
        scroll();
        column = 0;
    }
}

void scroll()
{
    for (u16 y = 1; y < VGA_HEIGHT; y++)
    {
        for (u16 x = 0; x < VGA_WIDTH; x++)
        {
            const u16 index = (y - 1) * VGA_WIDTH + x;
            const u16 nextIndex = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_buffer[nextIndex];
        }
    }

    for (u16 x = 0; x < VGA_WIDTH; x++)
    {
        const u16 index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        vga_buffer[index] = ' ' | defaultColor;
    }
}

void print(const char* s)
{
    while (*s)
    {
        if (*s == '\n')
        {
            newline();
        } else if (*s == '\r')
        {
            column = 0;
        } else if (*s == '\t')
        {
            if (column == VGA_WIDTH)
            {
                newline();
            } 
            u16 len = 4 - (column % 4);

            while (len--)
            {
                const u16 index = row * VGA_WIDTH + column;
                vga_buffer[index] = ' ' | currentColor;
                column++;
            }
        } else
        {
            const u16 index = row * VGA_WIDTH + column;
            vga_buffer[index] = *s | currentColor;
            column++;
            if (column >= VGA_WIDTH)
            {
                newline();
            }
        }
        s++;
    }
}

void print_int(int num)
{
    char buffer[12]; // Достаточно для хранения 32-битного целого числа
    itoa(num, buffer, 10); // Преобразование числа в строку
    print(buffer);
}