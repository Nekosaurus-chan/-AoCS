#pragma once

#include "../lib/stdint.h"

#define COLOR_BLACK         0
#define COLOR_LIGHT_GREY    7

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void print(const char* s);
void scroll();
void clear();
void newline();
void print_int(int num); // Добавьте объявление функции print_intяяя