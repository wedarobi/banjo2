#ifndef __ENUM_BEHAVIOUR__
#define __ENUM_BEHAVIOUR__

#include "include/enum/flag.h"



/**
 * A direct shifted mirror of the ABILITY flags in [flag.h]
 */
typedef enum
{
    /* 00 */ ABILITY_00_BK_BEAK_BARGE,
    /* 01 */ ABILITY_01_BK_BEAK_BOMB,
    /* 02 */ ABILITY_02_BK_BEAK_BUSTER,
    /* 03 >>>>>>>>>>>> */ ABILITY_03_UNK,
    /* 04 */ ABILITY_04_BK_STANDING_PECK,
    /* 05 */ ABILITY_05_BK_CLIMB_TREES,
    /* 06 */ ABILITY_06_BK_USE_EGGS,
    /* 07 */ ABILITY_07_BK_FEATHERY_FLAP,
    /* 08 */ ABILITY_08_BK_FLAP_FLIP,
    /* 09 */ ABILITY_09_BK_FLYING,
    /* 0A */ ABILITY_0A_BK_FULL_JUMP_HEIGHT,
    /* 0B */ ABILITY_0B_BK_RAT_A_TAT_RAP,
    /* 0C */ ABILITY_0C_BK_ROLL,
    /* 0D */ ABILITY_0D_BK_SHOCK_SPRING_JUMP,
    /* 0E */ ABILITY_0E_BK_WADING_BOOTS,
    /* 0F */ ABILITY_0F_BK_DIVING,
    /* 10 */ ABILITY_10_BK_TALON_TROT,
    /* 11 */ ABILITY_11_BK_SPEED_SHOES,
    /* 12 */ ABILITY_12_BK_WONDERWING,
    /* 13 >>>>>>>>>>>> */ ABILITY_13_UNK,
    /* 14 */ ABILITY_14_GRIP_GRAB,
    /* 15 */ ABILITY_15_BREEGULL_BLASTER,
    /* 16 */ ABILITY_16_EGG_AIM,
    /* 17 >>>>>>>>>>>> */ ABILITY_17_UNK,
    /* 18 >>>>>>>>>>>> */ ABILITY_18_UNK,
    /* 19 */ ABILITY_19_BILL_DRILL,
    /* 1A */ ABILITY_1A_BEAK_BAYONET,
    /* 1B */ ABILITY_1B_AIRBORNE_EGG_AIM,
    /* 1C */ ABILITY_1C_SPLIT_UP,
    /* 1D */ ABILITY_1D_WING_WHACK,
    /* 1E */ ABILITY_1E_TALON_TORPEDO,
    /* 1F */ ABILITY_1F_SUB_AQUA_EGG_AIM,
    /* 20 */ ABILITY_20_TREX_ROAR,
    /* 21 */ ABILITY_21_SHACK_PACK,
    /* 22 */ ABILITY_22_GLIDE,
    /* 23 */ ABILITY_23_SNOOZE_PACK,
    /* 24 */ ABILITY_24_LEG_SPRING,
    /* 25 */ ABILITY_25_CLAW_CLAMBER_BOOTS,
    /* 26 */ ABILITY_26_SPRINGY_STEP_SHOES,
    /* 27 */ ABILITY_27_TAXI_PACK,
    /* 28 */ ABILITY_28_HATCH_EGGS,
    /* 29 */ ABILITY_29_PACK_WHACK,
    /* 2A */ ABILITY_2A_SACK_PACK,
    /* 2B */ ABILITY_2B_AMAZE_O_GAZE_GOGGLES,
    /* 2C */ ABILITY_2C_EGGS_FIRE,
    /* 2D */ ABILITY_2D_EGGS_GRENADE,
    /* 2E */ ABILITY_2E_EGGS_CLOCKWORK,
    /* 2F */ ABILITY_2F_EGGS_ICE,
    /* 30 */ ABILITY_30_FAST_SWIMMING,
    /* 31 */ ABILITY_31_EGGS_BLUE,
    /* 32 */ ABILITY_32_BREEGULL_BASH,
#if VERSION_USA
    /* 33 >>>>>>>>>>>> */ ABILITY_33_UNK,
    /* 34 >>>>>>>>>>>> */ ABILITY_34_UNK,
    /* 35 >>>>>>>>>>>> */ ABILITY_35_UNK,
    /* 36 >>>>>>>>>>>> */ ABILITY_36_UNK,
    /* 37 >>>>>>>>>>>> */ ABILITY_37_UNK,
    /* 38 >>>>>>>>>>>> */ ABILITY_38_UNK,
    /* 39 >>>>>>>>>>>> */ ABILITY_39_UNK,
    /* 3A >>>>>>>>>>>> */ ABILITY_3A_UNK,
    /* 3B >>>>>>>>>>>> */ ABILITY_3B_UNK,
    /* 3C >>>>>>>>>>>> */ ABILITY_3C_UNK,
    /* 3D >>>>>>>>>>>> */ ABILITY_3D_UNK,
    /* 3E >>>>>>>>>>>> */ ABILITY_3E_UNK,
    /* 3F >>>>>>>>>>>> */ ABILITY_3F_UNK,
    /* 40 >>>>>>>>>>>> */ ABILITY_40_UNK,
    /* 41 >>>>>>>>>>>> */ ABILITY_41_UNK,
    /* 42 >>>>>>>>>>>> */ ABILITY_42_UNK,
    /* 43 >>>>>>>>>>>> */ ABILITY_43_UNK,
    /* 44 >>>>>>>>>>>> */ ABILITY_44_UNK,
    /* 45 >>>>>>>>>>>> */ ABILITY_45_UNK,
    /* 46 >>>>>>>>>>>> */ ABILITY_46_UNK,
    /* 47 >>>>>>>>>>>> */ ABILITY_47_UNK,
    /* 48 >>>>>>>>>>>> */ ABILITY_48_UNK,
    /* 49 >>>>>>>>>>>> */ ABILITY_49_UNK,
    /* 4A >>>>>>>>>>>> */ ABILITY_4A_UNK,
    /* 4B >>>>>>>>>>>> */ ABILITY_4B_UNK,
    /* 4C >>>>>>>>>>>> */ ABILITY_4C_UNK,
    /* 4D >>>>>>>>>>>> */ ABILITY_4D_UNK,
    /* 4E >>>>>>>>>>>> */ ABILITY_4E_UNK,
    /* 4F >>>>>>>>>>>> */ ABILITY_4F_UNK,
    /* 50 >>>>>>>>>>>> */ ABILITY_50_UNK,
#else
    // [see gcegg.c]
    /* 33 >>>>>>>>>>>> */ ABILITY_3C_UNK,
#endif

    ABILITY_MAX
} ABILITY;




















#endif // __ENUM_BEHAVIOUR__








