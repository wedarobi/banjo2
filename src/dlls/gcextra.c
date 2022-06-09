#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"

#include "include/enum/flag.h"



s32 DLL_gcextra_00_get_spent_honey_flags(void)
{
    return fn_flag_get_multi(FLAG_4EA_HONEY_B_HONEY_UPGRADES_1, 3);
}

s32 DLL_gcextra_01_get_max_health_upgrade_count(void)
{
    return 5;
}

s32 DLL_gcextra_02_increment_spent_honey_flags(s32 increment)
{
    s32 next = DLL_gcextra_00_get_spent_honey_flags() + increment;
    s32 max  = DLL_gcextra_01_get_max_health_upgrade_count();

    if (next > max)
        next = max;

    fn_flag_set_multi(FLAG_4EA_HONEY_B_HONEY_UPGRADES_1, next, 3);
    func_800D517C();
}











