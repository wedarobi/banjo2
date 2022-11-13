#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"


#include "include/enum/map.h"
#include "include/enum/minigame.h"
#include "include/bootcode_cipher.h"


#define SPITEM_JIGGIES (1)


static struct
{
/* 00 */ u8  UNK_00;
/* 01 */ u8  UNK_01;
/* 02 */ u8  UNK_02;
/* 03 */ u8  UNK_03;
//# after decryption, add [MAP_0A0_MIN] to get the real value
/* 04 */ u32 encryptedPuzzleMapIdx;
/* 08 */ u8  UNK_08;
/* 09 */ u8  UNK_09;
/* 0A */ u8  abilityIdx;
/* 0B */ u8  UNK_0B;
//# after decryption, add [MAP_0A0_MIN] to get the real value
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
/*  0 */ { 0x01, 0x0, 0x0, 0x0, BCCI_0025, 0x1, 0x64, 0x0, 0x0, BCCI_00AF, 0x7A, 0xF, 0x0, 0x0, 0x391, 0x0, 0x0 },
/*  1 */ { 0x04, 0x0, 0x0, 0x0, BCCI_0038, 0x1, 0x64, 0x0, 0x0, BCCI_00B2, 0x7B, 0xD, 0x0, 0x0, 0x393, 0x0, 0x0 },
/*  2 */ { 0x08, 0x0, 0x0, 0x0, BCCI_0041, 0x1, 0x64, 0x0, 0x0, BCCI_00B4, 0x7C, 0xB, 0x0, 0x0, 0x489, 0x0, 0x0 },
/*  3 */ { 0x0E, 0x0, 0x0, 0x0, BCCI_0054, 0x1, 0x64, 0x0, 0x0, BCCI_00B5, 0x7D, 0x9, 0x0, 0x0, 0x392, 0x0, 0x0 },
/*  4 */ { 0x14, 0x0, 0x0, 0x0, BCCI_0074, 0x1, 0x64, 0x0, 0x0, BCCI_00BA, 0x7E, 0x7, 0x0, 0x0, 0x396, 0x0, 0x0 },
/*  5 */ { 0x1C, 0x0, 0x0, 0x0, BCCI_0067, 0x1, 0x64, 0x0, 0x0, BCCI_00BC, 0x7F, 0x5, 0x0, 0x0, 0x4DB, 0x0, 0x0 },
/*  6 */ { 0x24, 0x0, 0x0, 0x0, BCCI_0089, 0x1, 0x64, 0x0, 0x0, BCCI_00B5, 0x80, 0x4, 0x0, 0x1, 0x394, 0x0, 0x0 },
/*  7 */ { 0x2D, 0x0, 0x0, 0x0, BCCI_009A, 0x1, 0x64, 0x0, 0x0, BCCI_00BA, 0x81, 0x3, 0x0, 0x1, 0x412, 0x0, 0x0 },
/*  8 */ { 0x37, 0x0, 0x0, 0x0, BCCI_00BD, 0x1, 0x64, 0x0, 0x0, BCCI_00BC, 0x82, 0x2, 0x0, 0x1, 0x48D, 0x0, 0x0 },
/*  9 */ { 0x46, 0x0, 0x0, 0x0, BCCI_00C0, 0x1, 0x64, 0x0, 0x0, BCCI_00BD, 0x83, 0x0, 0x0, 0x0, 0x48D, 0x0, 0x0 },
/* 10 */ { 0x00, 0x0, 0x0, 0x0, BCCI_00B1, 0x1, 0x64, 0x0, 0x0, BCCI_0000, 0x0,  0x0, 0xF, 0x0, 0x000, 0x0, 0x0 },
};

#define HI(x) ((x & 0xFFFF0000) >> 0x10)
#define LO(x)  (x & 0x0000FFFF)

// TODO v1 + stack -> s0
static MAP decrypt_map_with_bootcode(u32 encryptedMap)
{
    u32 tmp;

    u32 i0;
    u32 a2;

    u32 s0;

    i0 = LO(encryptedMap);

    a2 = HI(encryptedMap);

    i0 += 0xB0000000;

    if ((i0 & 2) != 0)
    {
        u32 tmp0;
        fn_rom_fetch_WORD(i0 >> 2 << 2, &tmp0);
        s0 = HI(tmp0);
    }
    else
    {
        u32 tmp0;
        fn_rom_fetch_WORD(i0, &tmp0);
        s0 = LO(tmp0);
    }

    if (a2 != 0)
    {
        a2 += 0xB0000000;

        if ((a2 & 2) != 0)
        {
            fn_rom_fetch_WORD(a2 >> 2 << 2, &tmp);
            s0 = tmp;
            s0 += HI(s0);
        }
        else
        {
            fn_rom_fetch_WORD(a2, &tmp);
            s0 = tmp;
            s0 += LO(s0);
        }
    }

    s0 += MAP_0A0_MIN;

    return s0;
}

s32 DLL_sujiggy_00_completed_puzzle_flags_get(void)
{
    return fn_flag_get_multi(FLAG_35C_JIGGYWIGGY_CHALLENGE_COMPLETION_1, 4);
}

s32 DLL_sujiggy_01_total_puzzle_count_get(void)
{
    return 11;
}

s32 DLL_sujiggy_02(s32 a0)
{
    return mapInfo[a0].UNK_00;
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
    s32 completedFlags;
    u32 tmp0;
    MAP map;

    completedFlags = DLL_sujiggy_00_completed_puzzle_flags_get();

    if (!fn_flag_get(FLAG_3E9_ATTEMPTED_JIGGYWIGGY_PUZZLE))
    {
        fn_flag_set_multi(GFLAG_C0D_UNK, 0, 8);
        fn_flag_set_multi(FLAG5_D57_UNK, 0, 4);
    }

    fn_flag_set_FALSE(FLAG5_D4D_UNK);
    fn_flag_set_TRUE(FLAG5_D4E_UNK);

    if (completedFlags >= 10)
        fn_flag_set(FLAG5_D49_TEMPCOPY_ATTEMPTED_JIGGYWIGGY_PUZZLE, fn_flag_get(FLAG_589_ATTEMPTED_JIGGYWIGGY_SPECIAL_PUZZLE));
    else
        fn_flag_set(FLAG5_D49_TEMPCOPY_ATTEMPTED_JIGGYWIGGY_PUZZLE, fn_flag_get(FLAG_3E9_ATTEMPTED_JIGGYWIGGY_PUZZLE));

#if VERSION_USA
    fn_flag_set(FLAG5_D74_UNK, fn_flag_get(FLAG_57B_UNK));
#else
    fn_flag_set(FLAG5_D6A_UNK, fn_flag_get(FLAG_57B_UNK));
#endif

    fn_flag_set_multi(FLAG5_D50_UNK, completedFlags, 4);

#if VERSION_USA
    fn_flag_set_FALSE(FLAG5_D73_UNK);
#endif

    gMusicObj_playThroughLz_set(2);
    gMusicObj_0x17_set(1);
    MUSIC_play_sfx_2_bgm(MUSIC_2E_PUZZLE_START);
    null_800A9B84();
    jiggywiggy_map_store_temple_in_temp_map_flags(MAP_151_IOH_JIGGYWIGGYS_TEMPLE, 3);

    map  = DLL_sujiggy_04(completedFlags);
    tmp0 = DLL_sujiggy_05(completedFlags);

    tmt_gameover_orchestrate_UNK(1, map, tmp0);
}

void DLL_sujiggy_09(void)
{
    fn_flag_set_TRUE(FLAG5_D4D_UNK);
}

void DLL_sujiggy_10(void)
{
    gMusicObj_playThroughLz_set(2);
    gMusicObj_0x17_set(1);
    fn_flag_set_TRUE(FLAG5_D4F_UNK);

    if (fn_flag_get(FLAG5_D4D_UNK))
        fn_flag_set_multi(FLAG5_D57_UNK, 0, 4);
    else
        fn_flag_set_multi(FLAG5_D57_UNK, DLL_sujiggy_19() + 1, 4);

    jiggywiggy_return_from_puzzle();
}

void DLL_sujiggy_11(u32 a0)
{
    u32 tmp0;
    MAP map;

    MUSIC_play_sfx_2_bgm(MUSIC_2E_PUZZLE_START);
    gMusicObj_playThroughLz_set(2);
    gMusicObj_0x17_set(1);
    fn_flag_set_multi(FLAG5_D57_UNK, DLL_sujiggy_19() + 1, 4);

    map  = DLL_sujiggy_04(a0);
    tmp0 = DLL_sujiggy_05(a0);

    tmt_gameover_orchestrate_UNK(1, map, tmp0);
}

u32 DLL_sujiggy_12(void)
{
    return fn_flag_get_multi(FLAG5_D50_UNK, 4);
}

u32 DLL_sujiggy_13(void)
{
    return fn_flag_get(FLAG5_D4F_UNK);
}

u32 DLL_sujiggy_14(void)
{
    bool tmp0;

    if (DLL_sujiggy_21())
        tmp0 = fn_flag_get(FLAG5_D4D_UNK) ? 2 : 3;
    else
        tmp0 = fn_flag_get(FLAG5_D4D_UNK) ? 1 : 0;

   fn_flag_set_multi(FLAG_35C_JIGGYWIGGY_CHALLENGE_COMPLETION_1, fn_flag_get_multi(FLAG5_D50_UNK, 4), 4);

    if (DLL_sujiggy_21())
    {
        fn_flag_set(
            FLAG_589_ATTEMPTED_JIGGYWIGGY_SPECIAL_PUZZLE,
            fn_flag_get(FLAG5_D49_TEMPCOPY_ATTEMPTED_JIGGYWIGGY_PUZZLE)
        );
    }
    else
    {
        fn_flag_set(
            FLAG_3E9_ATTEMPTED_JIGGYWIGGY_PUZZLE,
            fn_flag_get(FLAG5_D49_TEMPCOPY_ATTEMPTED_JIGGYWIGGY_PUZZLE)
        );
    }

    fn_flag_set(FLAG_57B_UNK, fn_flag_get(FLAG5_D74_UNK));

    if (tmp0 == 1)
        fn_flag_get_and_increment_multi(FLAG_35C_JIGGYWIGGY_CHALLENGE_COMPLETION_1, 4);

    fn_flag_set_FALSE(FLAG5_D4F_UNK);
    fn_flag_set_FALSE(FLAG5_D4E_UNK);

#if VERSION_USA
    if (fn_flag_get(FLAG5_D73_UNK))
    {
        minigame_highscore_set(1, MINIGAME_JIGGYWIGGY_FINAL_PUZZLE, DLL_sujiggy_24());
        fn_flag_set_FALSE(FLAG5_D73_UNK);
    }
#endif

    return tmp0;
}

void DLL_sujiggy_15(s32 a0, s32 a1)
{
    if (fn_flag_get(FLAG_58A_UNK))
    {
        DLL_glcutDll_06(
            decrypt_map_with_bootcode(mapInfo[a0].encryptedLevelEntranceMapIdx),
            0x7A + a0
        );
    }
    else if (a1 != 0)
    {
        DLL_glcutDll_06(MAP_14F_IOH_WOODED_HOLLOW, 0x67);
    }
    else
    {
        fn_flag_set_TRUE(FLAG_58A_UNK);
        DLL_glcutDll_24(
            decrypt_map_with_bootcode(mapInfo[a0].encryptedLevelEntranceMapIdx),
            MAP_151_IOH_JIGGYWIGGYS_TEMPLE,
            0x7A + a0
        );
    }
}

u32 DLL_sujiggy_16(void)
{
    u32 val = DLL_sujiggy_00_completed_puzzle_flags_get();
    s32 res;

    if (val == DLL_sujiggy_01_total_puzzle_count_get())
        return 0;

    res = DLL_sujiggy_02(val) - fn_SPITEM_count_get(SPITEM_JIGGIES);

    return res > 0 ? res : 0;
}

s32 DLL_sujiggy_17(void)
{
    u32 val = DLL_sujiggy_00_completed_puzzle_flags_get();

    if (val == DLL_sujiggy_01_total_puzzle_count_get())
        return -1;

    return fn_SPITEM_count_get(SPITEM_JIGGIES) >= DLL_sujiggy_02(val)
        ? 1
        : 0;
}

bool DLL_sujiggy_18(void)
{
    return DLL_sujiggy_19() > 2;
}

s32 DLL_sujiggy_19(void)
{
    return fn_flag_get_multi(FLAG5_D57_UNK, 4);
}

bool DLL_sujiggy_20(s32 a0)
{
    return DLL_glcutDll_19(0x7A + a0) == FALSE
        && DLL_sujiggy_00_completed_puzzle_flags_get() > a0
        && fn_flag_get(FLAG_392_PROGRESS_OPENED_WORLD_MT + a0) == FALSE;
}

bool DLL_sujiggy_21(void)
{
    s32 flags = fn_flag_get(FLAG5_D4E_UNK)
        ? fn_flag_get_multi(FLAG5_D50_UNK, 4)
        : DLL_sujiggy_00_completed_puzzle_flags_get();

    return flags > 9;
}

u8 DLL_sujiggy_22(s32 a0)
{
    return mapInfo[a0].UNK_13;
}

/* enum ACTOR */
u16 DLL_sujiggy_23(s32 a0)
{
    return mapInfo[a0].doorActorIdx;
}

u32 DLL_sujiggy_24(void)
{
    return fn_flag_get_multi(GFLAG_C0D_UNK, 8);
}

u32 DLL_sujiggy_25(s32 a0)
{
    s32 flags = DLL_sujiggy_24();

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



