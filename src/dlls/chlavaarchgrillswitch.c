#include "include/types.h"

#include "include/struct/object.h"

#include "include/hacks/helpers.h"


static u32 fn_priv_00_switch_interaction_handler(u32 a0, u32 a1, u32 a2)
{
    return 0;
}

static void fn_priv_01_switch_init(u32 a0)
{

}


static AIDS aids_00 =
{
    0x343,
    0x287,
    0x8D9,
    1,
    (void *)VER_SWITCH(0x8011A2C0, 0x80114580, 0x8011F3B0, 0x8011F1F0),
    (void *)VER_SWITCH(0x80085828, 0x80084EC8, 0x8008FB18, 0x8008FB18),
    (void *)VER_SWITCH(0x80105834, 0x80100104, 0x8010AF34, 0x8010AD74),
    (void *)VER_SWITCH(0x80101870, 0x800FC260, 0x80107090, 0x80106ED0),
    0,
    0,
    0,
    0,
    0,
/* 0x20 */
    0,
    0,
    0x00000888,
    NULL,
    (void *)VER_SWITCH(0x800857E0, 0x80084E80, 0x8008FAD0, 0x8008FAD0),
    0,
    0,
    (void *)fn_priv_01_switch_init,
    (void *)VER_SWITCH(0x80107C2C, 0x8010244C, 0x8010D27C, 0x8010D0BC),
    0x80002000,
    (void *)fn_priv_00_switch_interaction_handler,
    0,
};

AIDS *DLL_chlavaarchgrillswitch_00(void)
{
    return &aids_00;
}





