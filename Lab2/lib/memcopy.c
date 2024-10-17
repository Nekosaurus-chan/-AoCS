#include "memcopy.h"

void* memcpy(void* dest, const void* src, u32 n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;

    for (u32 i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}