#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"


#include "include/enum/map.h"





struct
{
/* 00 */ u8  UNK_00;
/* 01 */ u8  UNK_01;
/* 02 */ u8  UNK_02;
/* 03 */ u8  UNK_03;
/* 04 */ u32 encryptedPuzzleMapIdx;
/* 08 */ u8  UNK_08;
/* 09 */ u8  UNK_09;
/* 0A */ u8  UNK_0A;
/* 0B */ u8  UNK_0B;
/* 0C */ u32 encryptedLevelEntranceMapIdx;
/* 10 */ u8  UNK_10;
/* 11 */ u8  numPiecesPlaced;
/* 12 */ u8  UNK_12;
/* 13 */ u8  UNK_13;
             /* enum ACTOR */
/* 14 */ u16 doorActorIdx;
/* 16 */ u8  UNK_16;
/* 17 */ u8  UNK_17;
}
mapInfo[] =
{
// /*  0 */ {},
// /*  1 */ {},
// /*  2 */ {},
// /*  3 */ {},
// /*  4 */ {},
// /*  5 */ {},
// /*  6 */ {},
// /*  7 */ {},
// /*  8 */ {},
// /*  9 */ {},
// /* 10 */ {},
0
};




static MAP decrypt_map_with_bootcode(u32 encryptedMap)
{

}

u32 DLL_sujiggy_00_completed_puzzle_flags_get(void)
{
    return fn_flag_get_multi(FLAG_35C_JIGGYWIGGY_CHALLENGE_COMPLETION_1, 4);
}

u32 DLL_sujiggy_01_total_puzzle_count_get(void)
{
    return 11;
}

u8 DLL_sujiggy_02(s32 a0)
{

}

f32 DLL_sujiggy_03(s32 a0)
{
    return DLL_glreflight_00() & mapInfo[a0].UNK_09 & 0x7F;
}

MAP DLL_sujiggy_04(s32 a0)
{
    return decrypt_map_with_bootcode(mapInfo[a0].encryptedPuzzleMapIdx);
}

u8 DLL_sujiggy_05(s32 a0)
{
    return mapInfo[a0].UNK_08;
}

u8 DLL_sujiggy_06(s32 a0)
{
    return mapInfo[a0].numPiecesPlaced;
}

u8 DLL_sujiggy_07(s32 a0)
{
    return mapInfo[a0].UNK_12;
}

void DLL_sujiggy_08(void)
{
    fn_flag_set_TRUE(FLAG5_D4D_UNK);
}

void DLL_sujiggy_09(void)
{

}

void DLL_sujiggy_10(void)
{

}

u32 DLL_sujiggy_11(void)
{
    return fn_flag_get_multi(FLAG5_D50_UNK, 4);
}

u32 DLL_sujiggy_12(void)
{
    return fn_flag_get(FLAG5_D4F_UNK);
}

u32 DLL_sujiggy_13(void)
{

}

u32 DLL_sujiggy_14(s32 a0, s32 a1)
{

}

u32 DLL_sujiggy_15(void)
{

}

u32 DLL_sujiggy_16(void)
{

}

bool DLL_sujiggy_17(void)
{
    return DLL_sujiggy_18() > 2;
}

s32 DLL_sujiggy_18(void)
{
    return fn_flag_get_multi(FLAG5_D57_UNK, 4);
}

bool DLL_sujiggy_19(s32 a0)
{

}

bool DLL_sujiggy_20(void)
{
    s32 flags = fn_flag_get(FLAG5_D4E_UNK)
        ? fn_flag_get_multi(FLAG5_D50_UNK, 4)
        : DLL_sujiggy_00_completed_puzzle_flags_get();

    return flags > 9;
}

u8 DLL_sujiggy_21(s32 a0)
{
    return mapInfo[a0].UNK_13;
}

/* enum ACTOR */
u16 DLL_sujiggy_22(s32 a0)
{
    return mapInfo[a0].doorActorIdx;
}

u32 DLL_sujiggy_23(void)
{
    return fn_flag_get_multi(GFLAG_C0D_UNK, 8);
}

u32 DLL_sujiggy_24(s32 a0)
{
    s32 flags = DLL_sujiggy_23();

    if (a0 == 0)
    {
        return 0;
    }
    else if (flags == 0 || flags > a0)
    {
        fn_flag_set_multi(GFLAG_C0D_UNK, a0, 8);

        return 2;
    }
    else if (flags == a0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}






















