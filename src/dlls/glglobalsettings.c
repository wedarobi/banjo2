#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"







void DLL_glglobalsettings_00_set_default_settings_to_gflags(void)
{
    DLL_glglobalsettings_04_set_widescreen_to_gflags(FALSE);
    DLL_glglobalsettings_06_set_screen_to_gflags(0, 0);
    DLL_glglobalsettings_08_set_sound_mode_to_gflags(1);
}

static void apply_settings_from_gflags(void)
{
    s32 val1, val2;

    DLL_glglobalsettings_04_set_widescreen_to_gflags(DLL_glglobalsettings_03_get_widescreen_from_gflags());
    DLL_glglobalsettings_08_set_sound_mode_to_gflags(DLL_glglobalsettings_07_get_sound_mode_from_gflags());
    DLL_glglobalsettings_05_get_screen_from_gflags(&val1, &val2);
    DLL_glglobalsettings_06_set_screen_to_gflags(val1, val2);
}

static void *allocate_global_data_space(void)
{
    return fn_malloc_temp(0x80);
}

/*static*/ s32 load_global_data_from_EEP(s32 a0, void *a1)
{
    // TODO



}

/*static*/ void corrupt_global_data_header(s32 a0)
{
    // TODO



}

static s32 load_global_data_from_eep_to_buffer(void **ptr)
{
    // TODO



}

void DLL_glglobalsettings_01(void)
{
    void *p = allocate_global_data_space();

    s32 res = load_global_data_from_eep_to_buffer(&p);

    if (res == -1)
    {
        DLL_glglobalsettings_00_set_default_settings_to_gflags();
    }
    else
    {
        DLL_glglobaldata_02_load_global_data_into_memory(p);
        apply_settings_from_gflags();
    }

    fn_free(p);
}

/*static*/ s32 save_and_validate_global_data_slot(s32 a0, s32 a1)
{
    // TODO



}

s32 DLL_glglobalsettings_02_trigger_globaldata_save_to_EEP(void)
{
    // TODO


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

void DLL_glglobalsettings_05_get_screen_from_gflags(s32 *a0, s32 *a1)
{
    *a0 = fn_flag_get_multi(GFLAG_BBA_SCREEN_ALIGN_X_1, 6) - 32;
    *a1 = fn_flag_get_multi(GFLAG_BC0_SCREEN_ALIGN_Y_1, 6) - 32;
}

void DLL_glglobalsettings_06_set_screen_to_gflags(s32 a0, s32 a1)
{
    // TODO


}

s32 DLL_glglobalsettings_07_get_sound_mode_from_gflags(void)
{
    return fn_flag_get_multi(GFLAG_BC6_SPEAKER_MODE_1, 2);
}

void DLL_glglobalsettings_08_set_sound_mode_to_gflags(s32 value)
{
    // TODO


}


