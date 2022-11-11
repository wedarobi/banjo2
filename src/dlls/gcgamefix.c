#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"

#include "include/enum/item.h"


//# forward decls
static void fix_flags_canary_mary(void);
static void fix_flags_crushing_shed(void);
static void fix_flags_dippy_pool(void);
static void fix_flags_piglets_pool(void);
static void fix_flags_unk(void);


void DLL_gcgamefix_00_fix_game_flags(void)
{
    fix_flags_canary_mary();
    fix_flags_crushing_shed();
    fix_flags_dippy_pool();
#if !VERSION_USA
    fix_flags_piglets_pool();
#endif

    CONSUMABLE_change_held_count(0x4B, 0, 0);
    CONSUMABLE_change_held_count(0x4C, 0, 0);

#if VERSION_EUR
    fix_flags_unk();
#endif
}

void DLL_gcgamefix_01_fix_jinjo_jiggy_flags(s32 unused)
{
    u32 i;

    for (i = 0; i < TOTAL_JINJO_COLOURS; i++)
        if (JINJO_calc_collected_count(i) == JINJO_get_max_count(i))
            if (!SPECIAL_ITEM_collected_status(0x51 + i, SPECIAL_ITEMS_JIGGIES))
                SPECIAL_ITEM_JIGGIES_collected_set(0x51 + i, 1, 1);
}

static void fix_flags_canary_mary(void)
{
    if (fn_flag_get(FLAG_066_PROGRESS_GGM_CANARY_MARY_FREED_1))
        fn_flag_set_TRUE(FLAG_507_PROGRESS_GGM_CANARY_MARY_FREED_READY_TO_RACE);

    if (ITEM_is_spawned(4, SPECIAL_ITEMS_CHEATO_PAGES))
        fn_flag_set_TRUE(FLAG_504_PROGRESS_CANARY_MARY_IN_CCL);
}

static void fix_flags_crushing_shed(void)
{
    if (fn_flag_get(FLAG_4FC_UNK))
        fn_flag_set_TRUE(FLAG_4FD_UNK);

    if (fn_flag_get(FLAG_4FF_UNK))
        fn_flag_set_TRUE(FLAG_500_UNK);
}

static void fix_flags_dippy_pool(void)
{
    if (fn_flag_get(FLAG_327_UNK)
    &&  !SPECIAL_ITEM_collected_status(fJIG(FLAG_279_JIGGY_TDL_DIPPY), SPECIAL_ITEMS_JIGGIES))
    {
        SPECIAL_ITEM_JIGGIES_collected_set(fJIG(FLAG_279_JIGGY_TDL_DIPPY), 1, 1);
    }
}

#if !VERSION_USA
static void fix_flags_piglets_pool(void)
{
    if (fn_flag_get(FLAG_167_PHYSICAL_HFP_DrainedHotPool)
    &&  fn_flag_get(FLAG_166_UNK)
    &&  !SPECIAL_ITEM_collected_status(fJIG(FLAG_271_JIGGY_JRL_PIGLETS_POOL), SPECIAL_ITEMS_JIGGIES))
    {
        SPECIAL_ITEM_JIGGIES_collected_set(fJIG(FLAG_271_JIGGY_JRL_PIGLETS_POOL), 1, 1);
    }
}
#endif

#if VERSION_EUR
static void fix_flags_unk(void)
{
    if (fn_flag_get(FLAG_5A5_UNK))
    {
        fn_flag_set_TRUE(FLAG_08A_UNK);
        fn_flag_set_FALSE(FLAG_588_UNK);
    }

    if (fn_flag_get(FLAG_5A6_UNK))
    {
        fn_flag_set_TRUE(FLAG_15E_UNK);
        fn_flag_set_FALSE(FLAG_189_UNK);
    }
}
#endif

