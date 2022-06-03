#include "include/2.0L/ultra64.h"

#include "include/functions.h"

extern u32 DAT_8007DB54;

u32 DLL_glreflight_00(void)
{
    return DAT_8007DB54 ^ 0xACC903EE;
}


