#include "include/types.h"
#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"






void DLL_glglobalsettings_00_set_default_settings_to_gflags(void)
{
    DLL_glglobalsettings_04_set_widescreen_to_gflags(FALSE);

#if TVTYPE_NTSC
    DLL_glglobalsettings_06_set_screen_to_gflags(0, 0);
#elif TVTYPE_PAL
    DLL_glglobalsettings_06_set_screen_to_gflags(0, 0, 304, 268);
#endif

    DLL_glglobalsettings_08_set_sound_mode_to_gflags(1);

#if VERSION_EUR
    DLL_glglobalsettings_10_set_language_to_gflags(0);
#endif
}

#if TVTYPE_NTSC
static void apply_settings_from_gflags(void)
{
    s32 val1, val2;

    DLL_glglobalsettings_04_set_widescreen_to_gflags(DLL_glglobalsettings_03_get_widescreen_from_gflags());
    DLL_glglobalsettings_08_set_sound_mode_to_gflags(DLL_glglobalsettings_07_get_sound_mode_from_gflags());
    DLL_glglobalsettings_05_get_screen_from_gflags(&val1, &val2);
    DLL_glglobalsettings_06_set_screen_to_gflags(val1, val2);
}
#elif TVTYPE_PAL
static void apply_settings_from_gflags(void)
{
    s32 val1, val2, val3, val4;

    DLL_glglobalsettings_04_set_widescreen_to_gflags(DLL_glglobalsettings_03_get_widescreen_from_gflags());
    DLL_glglobalsettings_08_set_sound_mode_to_gflags(DLL_glglobalsettings_07_get_sound_mode_from_gflags());
    DLL_glglobalsettings_05_get_screen_from_gflags(&val1, &val2, &val3, &val4);
    DLL_glglobalsettings_06_set_screen_to_gflags(val1, val2, val3, val4);
}
#endif

static void *alloc_temp_globaldata_space(void)
{
    return fn_malloc_temp(0x80);
}

static s32 load_global_data_from_EEP(s32 a0, void *a1)
{
    s32 i;
    s32 res = 0;

    for (i = 3; i > 0; i--)
    {
        res = DLL_glgamestore_01_load_global_data_from_EEP(a0, a1);

        if (res == 0)
            break;
    }

    if (res != 0)
        DLL_glglobaldata_04_clear_global_data(a1);

    return res;
}

static void corrupt_global_data_header(s32 a0)
{
    s32 i;

    for (i = 0; i < 2; i++)
        if (i != a0)
            DLL_glgamestore_05_corrupt_global_data_header(i);
}

static s32 load_global_data_from_eep_to_buffer(void **ptr)
{
    void *space = alloc_temp_globaldata_space();

    s32 idxOfError = -1;
    s32 i          = 0;
    s32 errCount   = 0;

    for (; i < 2; i++)
    {
        if (load_global_data_from_EEP(i, space) == 0)
        {
            void *oldSpace = space;

            errCount++;
            idxOfError = i;

            space = *ptr;
            *ptr  = oldSpace;
        }
    }

    if (errCount > 1)
        corrupt_global_data_header(idxOfError);

    fn_free(space);

    return idxOfError;
}

void DLL_glglobalsettings_01(void)
{
    s32 res;

    void *space = alloc_temp_globaldata_space();

    res = load_global_data_from_eep_to_buffer(&space);

    if (res == -1)
    {
        DLL_glglobalsettings_00_set_default_settings_to_gflags();
    }
    else
    {
        DLL_glglobaldata_02_load_global_data_into_memory(space);
        apply_settings_from_gflags();
    }

    fn_free(space);
}

static s32 save_and_validate_global_data_slot(s32 a0, void *a1)
{
    s32 i   = 3;
    s32 res = 42069; //# gottem

    void *space = alloc_temp_globaldata_space();

    for (; res != 0 && i != 0; i--)
    {
        res = DLL_glgamestore_03_save_global_data_to_EEP(a0, a1);

        if (res == 0)
            load_global_data_from_EEP(a0, space);
    }

    fn_free(space);

    return res;
}

s32 DLL_glglobalsettings_02_trigger_globaldata_save_to_EEP(void)
{
    if (!fn_flag_get(FLAG5_D54_IF_GLOBALFLAGS_CHANGED))
    {
        return 0;
    }
    else
    {
        s32 res;
        s32 tmp;
        s32 i;

        void *space = alloc_temp_globaldata_space();

        tmp = load_global_data_from_eep_to_buffer(&space);

        DLL_glglobaldata_03_prepare_global_data_for_save(space);

        for (i = 0; i < 2; i++)
            if (i != tmp)
                break;

        res = save_and_validate_global_data_slot(i, space);

        if (res == 0)
        {
            corrupt_global_data_header(i);

            fn_flag_set_FALSE(FLAG5_D54_IF_GLOBALFLAGS_CHANGED);
        }

        fn_free(space);

        return res;
    }
}

bool DLL_glglobalsettings_03_get_widescreen_from_gflags(void)
{
    return fn_flag_get(GFLAG_BB9_WIDESCREEN_ENABLED);
}

void DLL_glglobalsettings_04_set_widescreen_to_gflags(s32 enabled)
{
    WIDESCREEN_set(enabled);
    fn_flag_set(GFLAG_BB9_WIDESCREEN_ENABLED, enabled ? TRUE : FALSE);
}

#if TVTYPE_NTSC
void DLL_glglobalsettings_05_get_screen_from_gflags(s32 *a0, s32 *a1)
{
    *a0 = fn_flag_get_multi(GFLAG_BBA_SCREEN_ALIGN_X_1, 6) - 32;
    *a1 = fn_flag_get_multi(GFLAG_BC0_SCREEN_ALIGN_Y_1, 6) - 40;
}

void DLL_glglobalsettings_06_set_screen_to_gflags(s32 a0, s32 a1)
{
    SCREEN_DIMENSIONS_set(a0, a1);

    a0 += 32;
    a1 += 40;

    if (a0 > 63)
        a0 = 63;

    if (a1 > 63)
        a1 = 63;

    fn_flag_set_multi(GFLAG_BBA_SCREEN_ALIGN_X_1, a0, 6);
    fn_flag_set_multi(GFLAG_BC0_SCREEN_ALIGN_Y_1, a1, 6);
}
#elif TVTYPE_PAL
void DLL_glglobalsettings_05_get_screen_from_gflags(s32 *a0, s32 *a1, s32 *a2, s32 *a3)
{
    *a0 = fn_flag_get_multi(GFLAG_BBA_SCREEN_ALIGN_X_1, 6) - 32;
    *a1 = fn_flag_get_multi(GFLAG_BC0_SCREEN_ALIGN_Y_1, 6) - 40;
    *a2 = fn_flag_get_multi(GFLAG_EURC19_SCREEN_SCALE_X_1, 6) + 289;
    *a3 = fn_flag_get_multi(GFLAG_EURC1F_SCREEN_SCALE_Y_1, 6) + 255;
}

void DLL_glglobalsettings_06_set_screen_to_gflags(s32 a0, s32 a1, s32 a2, s32 a3)
{
    SCREEN_DIMENSIONS_set(a0, a1, a2, a3);

    a0 += 32;
    a1 += 40;

    if (a0 > 63)
        a0 = 63;

    if (a1 > 63)
        a1 = 63;

    fn_flag_set_multi(GFLAG_BBA_SCREEN_ALIGN_X_1, a0, 6);
    fn_flag_set_multi(GFLAG_BC0_SCREEN_ALIGN_Y_1, a1, 6);

    a2 -= 289;
    a3 -= 255;

    if (a2 > 63)
        a2 = 63;

    if (a3 > 63)
        a3 = 63;

    fn_flag_set_multi(GFLAG_EURC19_SCREEN_SCALE_X_1, a2, 6);
    fn_flag_set_multi(GFLAG_EURC1F_SCREEN_SCALE_Y_1, a3, 6);
}
#endif

s32 DLL_glglobalsettings_07_get_sound_mode_from_gflags(void)
{
    return fn_flag_get_multi(GFLAG_BC6_SPEAKER_MODE_1, 2);
}

void DLL_glglobalsettings_08_set_sound_mode_to_gflags(s32 idx)
{
    static struct
    {
        s16 _1;
        s16 _2;
    }
    soundinfo[] =
    {
        { 1, 4 },
        { 2, 4 },
        { 3, 4 },
        { 4, 4 },
    };

    SOUND_MODE_unk1_set(   soundinfo[idx]._1);
    SOUND_MODE_unk2_set(0, soundinfo[idx]._2);
    SOUND_MODE_unk2_set(1, soundinfo[idx]._2);

    fn_flag_set_multi(GFLAG_BC6_SPEAKER_MODE_1, idx, 2);
}

#if VERSION_EUR
s32 DLL_glglobalsettings_09_get_language_from_gflags(void)
{
    return fn_flag_get_multi(GFLAG_EURC0D_LANGUAGE_1, 3);
}

void DLL_glglobalsettings_10_set_language_to_gflags(s32 lang)
{
    fn_flag_set_multi(GFLAG_EURC0D_LANGUAGE_1, lang, 3);
}
#endif


