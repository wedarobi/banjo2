#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"


#define SIZE_SLOT_NORMAL (0x1C0)
#define SIZE_SLOT_GLOBAL (0x80)


static s32 validate_savedata_crc(void *a0, s32 a1)
{
    s32 res = DLL_glcrc_01_crc_calc_and_validate(a0, a1);

    if (res != 0)
        res = 3;

    return res;
}

static s32 global_slot_size_for_count(s32 numSlots)
{
    return numSlots * SIZE_SLOT_GLOBAL;
}

static s32 get_eep_offset_for_slotidx(s32 slotIdxToLoad)
{
    /**
     * 2 * 0x80 == 0x100 (256 B)
     * 
     * Two global slots are reserved before normal slots in EEP.
     * One for global data, the other for the dummy slot for
     * atomic saves.
     */
    return global_slot_size_for_count(2) + slotIdxToLoad * SIZE_SLOT_NORMAL;
}

static s32 load_data_to_dst_and_validate_crc(s32 a0, void *a1, s32 a2)
{
    s32 res = 0;

    if (DLL_gleeprom_02(a0, a1, a2) != 0)
        res = 2;

    if (res == 0)
        res = validate_savedata_crc(a1, a2);

    return res;
}

s32 DLL_glgamestore_00_load_slot_data_from_EEP(s32 a0, void *dst)
{
    return load_data_to_dst_and_validate_crc(
        get_eep_offset_for_slotidx(a0),
        dst,
        SIZE_SLOT_NORMAL
    );
}

s32 DLL_glgamestore_01_load_global_data_from_EEP(s32 a0, void *dst)
{
    s32 res = load_data_to_dst_and_validate_crc(
        global_slot_size_for_count(a0),
        dst,
        SIZE_SLOT_GLOBAL
    );

    if (res == 0)
        //# crc check passed, now validate the header
        if (!DLL_glglobaldata_01_if_global_data_header_valid(dst))
            res = 2;

    return res;
}

static s32 save_data_to_EEP(s32 a0, void *a1, s32 a2)
{
    s32 res = 0;

    if (DAT_80079F5C == 2)
        if (DLL_gleeprom_01(a0, a1, a2))
            res = 1;

    return res;
}

s32 DLL_glgamestore_02_save_file_slot_to_EEP(s32 a0, void *a1)
{
    return save_data_to_EEP(get_eep_offset_for_slotidx(a0), a1, SIZE_SLOT_NORMAL);
}

s32 DLL_glgamestore_03_save_global_data_to_EEP(s32 a0, void *a1)
{
    return save_data_to_EEP(global_slot_size_for_count(a0), a1, SIZE_SLOT_GLOBAL);
}

static bool force_corrupt_slot_header(s32 a0)
{
    static u8 buf[0x08];

    s32 res = FALSE;

    if (DLL_gleeprom_01(a0, buf, 8))
        res = TRUE;

    return res;
}

bool DLL_glgamestore_04_corrupt_normal_slot_header(s32 a0)
{
    return force_corrupt_slot_header(get_eep_offset_for_slotidx(a0));
}

bool DLL_glgamestore_05_corrupt_global_slot_header(s32 a0)
{
    return force_corrupt_slot_header(global_slot_size_for_count(a0));
}



