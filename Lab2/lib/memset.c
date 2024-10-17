#include "memset.h"

void memset(void *dest, char val, u32 count)
{
    char *temp = (char*) dest;
    for (; count != 0; count--)
    {
        *temp++ = val;
    }
}