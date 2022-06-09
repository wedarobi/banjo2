#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"


// TODO: Cleanup later
//# Move index constant changes by version
#if VERSION_USA
#define MI3C (0x3C)
#else
#define MI3C (0x33)
#endif


static struct
{
    s16 UNK_00;
    s16 UNK_02;
    s16 UNK_04;
    s16 UNK_06;
    u8  UNK_08;
    u8  UNK_09;
    u8  moveIdx;
    u8  UNK_0B;
    u8  UNK_0C;
    u8  UNK_0D; // unused?
}
arr00[] =
{
    { 0x0158, 0x0071, 0x0000, 0x0004, 0x00, 0x40, MI3C, 0x01, 0x03, 0x00 },
    { 0x026C, 0x0071, 0x015A, 0x0004, 0x01, 0x40, 0x31, 0x01, 0x03, 0x00 },
    { 0x026D, 0x006E, 0x015B, 0x006A, 0x02, 0x41, 0x2C, 0x02, 0x04, 0x00 },
    { 0x026E, 0x006F, 0x015C, 0x006B, 0x03, 0x42, 0x2F, 0x00, 0x03, 0x00 },
    { 0x026F, 0x0070, 0x015D, 0x006C, 0x04, 0x43, 0x2D, 0x04, 0x0C, 0x00 },
    { 0x0270, 0x006D, 0x015E, 0x0069, 0x05, 0x44, 0x2E, 0x04, 0x04, 0x00 },
    { 0x016D, 0x0079, 0x0160, 0x0078, 0x06, 0x45, MI3C, 0x04, 0x03, 0x00 },
    { 0x0271, 0x0071, 0x015F, 0x0004, 0x07, 0x40, MI3C, 0x01, 0x05, 0x00 },
};


u8 DLL_gcegg_00(s32 a0)
{
    s32 i;

    for (i = 0; i < ARRLEN(arr00); i++)
        if (a0 == arr00[i].UNK_00)
            return arr00[i].UNK_08;

    return 0;
}

u8 DLL_gcegg_01(s32 a0)
{
    s32 i;

    for (i = 0; i < ARRLEN(arr00); i++)
        if (a0 == arr00[i].UNK_04)
            return arr00[i].UNK_08;

    return 0;
}

s32 DLL_gcegg_02(s32 a0)
{
    return arr00[a0].UNK_02;
}

s32 DLL_gcegg_03(s32 a0)
{
    return arr00[a0].UNK_06;
}

s32 DLL_gcegg_04(s32 a0)
{
    return arr00[a0].UNK_0C;
}

s32 DLL_gcegg_05(s32 a0)
{
    return arr00[a0].UNK_09;
}

bool DLL_gcegg_06(s32 a0)
{
    return arr00[a0].moveIdx == MI3C || fn_ability_has(arr00[a0].moveIdx);
}

s32 DLL_gcegg_07(s32 a0)
{
    s32 res;

    if (!func_800D3948())
        return 1;

    res = arr00[a0].UNK_0B;

    return res;
}


