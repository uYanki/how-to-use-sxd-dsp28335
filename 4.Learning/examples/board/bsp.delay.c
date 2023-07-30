#include "bsp.delay.h"

void FirewareDelay(u32 n)
{
    u16 i;
    u32 j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < 1e5; ++j)
            ;
    }
}
