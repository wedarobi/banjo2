#include "include/2.0L/ultra64.h"

#include "include/functions.h"



void DLL_dbpalette_00(u32 *a0, u32 a1, u32 *a2)
{
    a2[0] = a0[a1]         & 0xFF;
    a2[1] = a0[a1] >> 0x08 & 0xFF;
    a2[2] = a0[a1] >> 0x10 & 0xFF;
    a2[3] = a0[a1] >> 0x18 & 0xFF;
}

void DLL_dbpalette_01(u32 *a0, u32 a1, u32 *a2)
{
    a0[a1] = 0;
    a0[a1] |= a2[0];
    a0[a1] |= a2[1] << 0x08;
    a0[a1] |= a2[2] << 0x10;
    a0[a1] |= a2[3] << 0x18;
}



