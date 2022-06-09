#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"

#include "include/enum/music.h"



#define MUSIC_NONE (0x3FFF)

#define _MAP_CHUFFY_WW   (-6)
#define _MAP_CHUFFY_GGM  (-7)
#define _MAP_CHUFFY_GI   (-8)
#define _MAP_CHUFFY_TDL  (-9)
#define _MAP_CHUFFY_IOH  (-10)
#define _MAP_CHUFFY_HFPL (-11)
#define _MAP_CHUFFY_HFPI (-12)



static struct
{
    /* enum MAP */
    s16 map;

    /* enum MUSIC */
    s16 musicTrackIdx : 14;
    s16 UNK_02_b_0_2  : 2;

    s16 instrumentSet;
}
themes[] =
{
/*   0 */ { MAP_0A1_CUTSCENE_TWO_YEARS_HAVE_PASSED,           MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   1 */ { MAP_0A2_CUTSCENE_HAG_1_ARRIVES,                   MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   2 */ { MAP_0A3_CUTSCENE_SISTERS_ARRIVE,                  MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   3 */ { MAP_0A4_CUTSCENE_GRUNTILDA_REVIVED,               MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   4 */ { MAP_0A5_CUTSCENE_GRUNTILDA_SPELL,                 MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   5 */ { MAP_0A6_CUTSCENE_HAG_1_LEAVES,                    MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   6 */ { MAP_0A7_CUTSCENE_BANJO_VOW,                       MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*   7 */ { MAP_18B_INTRO_SCREEN,                             MUSIC_7D_CS_MAIN_INTRO,                 0, 0x00 },
/*   8 */ { MAP_193_CUTSCENE_BOTTLES_ENERGY_RESTORING,        MUSIC_NONE,                             0, 0x00 },
/*   9 */ { MAP_0A8_CUTSCENE_PLAYING_POKER,                   MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*  10 */ { MAP_0A9_CUTSCENE_EARTHQUAKE,                      MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*  11 */ { MAP_0AA_CUTSCENE_MUMBO_LOOK_OUTSIDE,              MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*  12 */ { MAP_0AB_CUTSCENE_MUMBO_WARN,                      MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*  13 */ { MAP_0AC_CUTSCENE_BANJO_HOUSE_DESTROYED,           MUSIC_7B_CS_INTRO,                      1, 0x00 },
/*  14 */ { MAP_18C_CUTSCENE_INTRO_TO_BOB,                    MUSIC_NONE,                             0, 0x00 },
/*  15 */ { MAP_18D_CUTSCENE_JINGALING_ZAPPED,                MUSIC_NONE,                             0, 0x00 },
/*  16 */ { MAP_194_CUTSCENE_BK_RUNNING_INTO_GUN_CHAMBER,     MUSIC_NONE,                             0, 0x00 },
/*  17 */ { MAP_195_CUTSCENE_BK_AT_BOBS_CONTROLS,             MUSIC_NONE,                             0, 0x00 },
/*  18 */ { MAP_18E_CUTSCENE_MEANWHILE_JINGALING_ZAPPING,     MUSIC_NONE,                             0, 0x00 },
/*  19 */ { MAP_18F_CUTSCENE_BOB_PREPARING_TO_FIRE,           MUSIC_NONE,                             0, 0x00 },
/*  20 */ { MAP_196_CUTSCENE_KICK_ABOUT,                      MUSIC_NONE,                             0, 0x00 },
/*  21 */ { MAP_197_CUTSCENE_I_WONDER_WHAT_WE_WILL_HIT,       MUSIC_NONE,                             0, 0x00 },
/*  22 */ { MAP_190_CUTSCENE_JINGALING_GETTING_ZAPPED,        MUSIC_NONE,                             0, 0x00 },
/*  23 */ { MAP_198_CUTSCENE_JINGALING_RESTORING,             MUSIC_NONE,                             0, 0x00 },
/*  24 */ { MAP_17E_CUTSCENE_ZOMBIFIED_THRONE_ROOM,           MUSIC_NONE,                             0, 0x00 },
/*  25 */ { MAP_199_CUTSCENE_ALL_JINJOS_HAPPY_AGAIN,          MUSIC_NONE,                             0, 0x00 },
/*  26 */ { MAP_191_CUTSCENE_SAD_PARTY_AT_BOTTLES,            MUSIC_NONE,                             0, 0x00 },
/*  27 */ { MAP_192_CUTSCENE_BOTTLES_EATING_BURNT_FOOD,       MUSIC_NONE,                             0, 0x00 },
/*  28 */ { MAP_19C_CUTSCENE_ROLL_THE_CREDITS,                MUSIC_82_CS_CREDITS,                    0, 0x00 },
/*  29 */ { MAP_19D_CUTSCENE_PARADE,                          MUSIC_82_CS_CREDITS,                    0, 0x00 },
/*  30 */ { MAP_167_PARADE_MT,                                MUSIC_NONE,                             0, 0x00 },
/*  31 */ { MAP_168_PARADE_HFP_ICY,                           MUSIC_NONE,                             0, 0x00 },
/*  32 */ { MAP_169_PARADE_JV_BOTTLES_HOUSE,                  MUSIC_NONE,                             0, 0x00 },
/*  33 */ { MAP_16A_PARADE_CK_GUN_CHAMBER,                    MUSIC_NONE,                             0, 0x00 },
/*  34 */ { MAP_0AD_SM_GRUNTYS_LAIR,                          MUSIC_34_GL_ENTRANCE,                   0, 0x00 },
/*  35 */ { MAP_0AE_SM_BEHIND_THE_WATERFALL,                  MUSIC_32_SM_MAIN,                       1, 0x02 },
/*  36 */ { MAP_0AF_SM_MAIN_AREA,                             MUSIC_32_SM_MAIN,                       1, 0x01 },
/*  37 */ { MAP_173_SM_BANJOS_HOUSE,                          MUSIC_33_BANJOS_HOUSE,                  0, 0x00 },
/*  38 */ { MAP_141_SM_BOSS_INSIDE_THE_DIGGER_TUNNEL,         MUSIC_32_SM_MAIN,                       1, 0x02 },
/*  39 */ { MAP_158_FILE_SELECT_SCREEN,                       MUSIC_67_FILE_SELECT,                   0, 0x00 },
/*  40 */ { MAP_0B8_MT_MAIN_AREA,                             MUSIC_39_MT_MAIN,                       1, 0x03 },
/*  41 */ { MAP_0B9_MT_PRISON_COMPOUND,                       MUSIC_39_MT_MAIN,                       1, 0x03 },
/*  42 */ { MAP_0BA_MT_COLUMNS_VAULT,                         MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  43 */ { MAP_0BB_MT_MAYAN_KICKBALL_STADIUM_LOBBY,          MUSIC_39_MT_MAIN,                       1, 0x05 },
/*  44 */ { MAP_0C6_MT_KICKBALL_ARENA_1,                      MUSIC_39_MT_MAIN,                       1, 0x08 },
/*  45 */ { MAP_0C8_MT_KICKBALL_ARENA_2,                      MUSIC_39_MT_MAIN,                       1, 0x08 },
/*  46 */ { MAP_0C9_MT_KICKBALL_ARENA_3,                      MUSIC_39_MT_MAIN,                       1, 0x08 },
/*  47 */ { MAP_0BC_MT_CODE_CHAMBER,                          MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  48 */ { MAP_0C4_MT_JADE_SNAKE_GROVE,                      MUSIC_39_MT_MAIN,                       1, 0x03 },
/*  49 */ { MAP_0C5_MT_TREASURE_CHAMBER,                      MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  50 */ { MAP_0B6_MT_WUMBAS_WIGWAM,                         MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/*  51 */ { MAP_0B7_MT_MUMBOS_SKULL,                          MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/*  52 */ { MAP_177_MT_TARGITZANS_SLIGHTLY_SACRED_CHAMBER,    MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  53 */ { MAP_178_MT_TARGITZANS_TEMPLE,                     MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  54 */ { MAP_179_MT_TARGITZANS_TEMPLE_LOBBY,               MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  55 */ { MAP_17A_MT_BOSS_TARGITZANS_REALLY_SACRED_CHAMBER, MUSIC_39_MT_MAIN,                       1, 0x06 },
/*  56 */ { MAP_17F_MT_KICKBALL_ARENA_4,                      MUSIC_39_MT_MAIN,                       1, 0x08 },
/*  57 */ { MAP_0C7_GGM_MAIN_AREA,                            MUSIC_3E_GGM_MAIN,                      1, 0x0B },
/*  58 */ { MAP_0CA_GGM_FUEL_DEPOT,                           MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  59 */ { MAP_0CB_GGM_CRUSHING_SHED,                        MUSIC_3E_GGM_MAIN,                      1, 0x0E },
/*  60 */ { MAP_0CC_GGM_FLOODED_CAVES,                        MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  61 */ { MAP_0CD_GGM_WATER_STORAGE,                        MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  62 */ { MAP_0CE_GGM_WATERFALL_CAVERN,                     MUSIC_3E_GGM_MAIN,                      1, 0x0D },
/*  63 */ { MAP_0CF_GGM_POWER_HUT_BASEMENT,                   MUSIC_3E_GGM_MAIN,                      1, 0x0D },
/*  64 */ { MAP_0D0_GGM_CHUFFYS_CAB,                          MUSIC_3E_GGM_MAIN,                      1, 0x0E },
/*  65 */ { MAP_0D1_GGM_BOSS_INSIDE_CHUFFYS_BOILER,           MUSIC_3E_GGM_MAIN,                      1, 0x0D },
/*  66 */ { MAP_0D2_GGM_GLOOMY_CAVERNS,                       MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  67 */ { MAP_0D3_GGM_GENERATOR_CAVERN,                     MUSIC_3E_GGM_MAIN,                      1, 0x0D },
/*  68 */ { MAP_0D4_GGM_POWER_HUT,                            MUSIC_3E_GGM_MAIN,                      1, 0x11 },
/*  69 */ { MAP_0D7_GGM_TRAIN_STATION,                        MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  70 */ { MAP_0D8_GGM_PROSPECTORS_HUT,                      MUSIC_3E_GGM_MAIN,                      1, 0x11 },
/*  71 */ { MAP_0DA_GGM_TOXIC_GAS_CAVE,                       MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  72 */ { MAP_0DB_GGM_CANARY_CAVE,                          MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  73 */ { MAP_0DC_GGM_ORDNANCE_STORAGE,                     MUSIC_85_GGM_ALTERNATE,                 0, 0x45 },
/*  74 */ { MAP_163_GGM_ORDNANCE_STORAGE_ENTRANCE,            MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/*  75 */ { MAP_0D9_GGM_MUMBOS_SKULL,                         MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/*  76 */ { MAP_0E9_GGM_WUMBAS_WIGWAM,                        MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/*  77 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,                 MUSIC_3E_GGM_MAIN,                      1, 0x0E },
/*  78 */ { MAP_16F_GGM_CANARY_MARY_RACE_1,                   MUSIC_3E_GGM_MAIN,                      1, 0x0B },
/*  79 */ { MAP_170_GGM_CANARY_MARY_RACE_2,                   MUSIC_3E_GGM_MAIN,                      1, 0x0B },
/*  80 */ { MAP_0D6_WW_MAIN_AREA,                             MUSIC_40_WW_MAIN,                       1, 0x13 },
/*  81 */ { MAP_124_WW_SAUCER_OF_PERIL,                       MUSIC_40_WW_MAIN,                       1, 0x13 },
/*  82 */ { MAP_0D5_WW_WUMBAS_WIGWAM,                         MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/*  83 */ { MAP_0DD_WW_DODGEM_DOME_LOBBY,                     MUSIC_40_WW_MAIN,                       1, 0x1A },
/*  84 */ { MAP_0DE_WW_DODGEM_CHALLENGE_1V1,                  MUSIC_40_WW_MAIN,                       1, 0x1A },
/*  85 */ { MAP_0DF_WW_DODGEM_CHALLENGE_2V1,                  MUSIC_40_WW_MAIN,                       1, 0x1A },
/*  86 */ { MAP_0E0_WW_DODGEM_CHALLENGE_3V1,                  MUSIC_40_WW_MAIN,                       1, 0x1A },
/*  87 */ { MAP_186_WW_DODGEMS,                               MUSIC_40_WW_MAIN,                       1, 0x1A },
/*  88 */ { MAP_0E1_WW_CRAZY_CASTLE_STOCKADE,                 MUSIC_40_WW_MAIN,                       1, 0x14 },
/*  89 */ { MAP_13B_WW_CRAZY_CASTLE_STOCKADE_SAUCER,          MUSIC_40_WW_MAIN,                       1, 0x14 },
/*  90 */ { MAP_0E2_WW_CRAZY_CASTLE_LOBBY,                    MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  91 */ { MAP_0E3_WW_CRAZY_CASTLE_PUMP_ROOM,                MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  92 */ { MAP_0E4_WW_BALLOON_BURST_GAME,                    MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  93 */ { MAP_17B_MULTIPLAYER_WW_BALLOON_BURST,             MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  94 */ { MAP_0E5_WW_HOOP_HURRY,                            MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  95 */ { MAP_17C_MULTIPLAYER_WW_JUMP_THE_HOOPS,            MUSIC_40_WW_MAIN,                       1, 0x1C },
/*  96 */ { MAP_0E6_WW_STAR_SPINNER,                          MUSIC_40_WW_MAIN,                       1, 0x16 },
/*  97 */ { MAP_13C_WW_STAR_SPINNER_SAUCER,                   MUSIC_40_WW_MAIN,                       1, 0x16 },
/*  98 */ { MAP_0E7_WW_THE_INFERNO,                           MUSIC_40_WW_MAIN,                       1, 0x18 },
/*  99 */ { MAP_0EA_WW_CAVE_OF_HORRORS,                       MUSIC_40_WW_MAIN,                       1, 0x18 },
/* 100 */ { MAP_0EB_WW_HAUNTED_CAVERN,                        MUSIC_40_WW_MAIN,                       1, 0x18 },
/* 101 */ { MAP_0EC_WW_TRAIN_STATION,                         MUSIC_40_WW_MAIN,                       1, 0x18 },
/* 102 */ { MAP_0F9_WW_BOSS_MR_PATCH,                         MUSIC_40_WW_MAIN,                       1, 0x17 },
/* 103 */ { MAP_176_WW_MUMBOS_SKULL,                          MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 104 */ { MAP_0ED_JRL_JOLLYS,                               MUSIC_45_JRL_MAIN,                      1, 0x1F },
/* 105 */ { MAP_0EE_JRL_PAWNOS_EMPORIUM,                      MUSIC_45_JRL_MAIN,                      1, 0x1F },
/* 106 */ { MAP_0EF_JRL_MUMBOS_SKULL,                         MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 107 */ { MAP_0F1_JRL_INSIDE_THE_UFO,                       MUSIC_NONE,                             0, 0x00 },
/* 108 */ { MAP_0F4_JRL_ANCIENT_SWIMMING_BATHS,               MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 109 */ { MAP_0F6_JRL_ELECTRIC_EELS_LAIR,                   MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 110 */ { MAP_0F7_JRL_SEAWEED_SANCTUM,                      MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 111 */ { MAP_0F8_JRL_INSIDE_THE_BIG_FISH,                  MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 112 */ { MAP_0FA_JRL_TEMPLE_OF_THE_FISHES,                 MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 113 */ { MAP_0FC_JRL_BOSS_LORD_WOO_FAK_FAK,                MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 114 */ { MAP_0FF_JRL_BLUBBERS_WAVE_RACE_HIRE,              MUSIC_45_JRL_MAIN,                      1, 0x1F },
/* 115 */ { MAP_120_JRL_WUMBAS_WIGWAM,                        MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 116 */ { MAP_125_GI_WATER_SUPPLY_PIPE,                     MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 117 */ { MAP_126_GGM_WATER_SUPPLY_PIPE,                    MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 118 */ { MAP_181_JRL_SEA_BOTTOM_CAVERN,                    MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 119 */ { MAP_182_MULTIPLAYER_JRL_SUBMARINE,                MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 120 */ { MAP_1A7_JRL_MAIN_AREA,                            MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 121 */ { MAP_1A6_JRL_SMUGGLERS_CAVERN,                     MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 122 */ { MAP_1A8_JRL_ATLANTIS,                             MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 123 */ { MAP_1A9_JRL_SEA_BOTTOM,                           MUSIC_45_JRL_MAIN,                      1, 0x1D },
/* 124 */ { MAP_112_TDL_MAIN_AREA,                            MUSIC_52_TDL_MAIN,                      1, 0x26 },
/* 125 */ { MAP_113_TDL_BOSS_TERRYS_NEST,                     MUSIC_4A_checkme,                       0, 0x00 },
/* 126 */ { MAP_114_TDL_TRAIN_STATION,                        MUSIC_52_TDL_MAIN,                      1, 0x26 },
/* 127 */ { MAP_115_TDL_OOGLE_BOOGLES_CAVE,                   MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 128 */ { MAP_116_TDL_INSIDE_THE_MOUNTAIN,                  MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 129 */ { MAP_117_TDL_RIVER_PASSAGE,                        MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 130 */ { MAP_118_TDL_STYRACOSAURUS_FAMILY_CAVE,            MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 131 */ { MAP_119_TDL_UNGA_BUNGAS_CAVE,                     MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 132 */ { MAP_11A_TDL_STOMPING_PLAINS,                      MUSIC_52_TDL_MAIN,                      1, 0x26 },
/* 133 */ { MAP_11B_TDL_BONFIRE_CAVERN,                       MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 134 */ { MAP_11E_TDL_WUMBAS_WIGWAM_SMALL,                  MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 135 */ { MAP_122_TDL_WUMBAS_WIGWAM_BIG,                    MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 136 */ { MAP_123_TDL_INSIDE_CHOMPAS_BELLY,                 MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 137 */ { MAP_183_MULTIPLAYER_TDL_CHOMPAS_BELLY,            MUSIC_52_TDL_MAIN,                      1, 0x27 },
/* 138 */ { MAP_171_TDL_MUMBOS_SKULL,                         MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 139 */ { MAP_100_GI_MAIN_AREA,                             MUSIC_3F_GI_MAIN,                       1, 0x29 },
/* 140 */ { MAP_101_GI_FLOOR_1,                               MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 141 */ { MAP_102_GI_TRAIN_STATION,                         MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 142 */ { MAP_103_GI_WORKERS_QUARTERS,                      MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 143 */ { MAP_104_GI_TRASH_COMPACTOR,                       MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 144 */ { MAP_105_GI_ELEVATOR_SHAFT,                        MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 145 */ { MAP_106_GI_FLOOR_2_MAIN,                          MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 146 */ { MAP_107_GI_FLOOR_2_ELECTROMAGNET_CHAMBER,         MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 147 */ { MAP_108_GI_FLOOR_3_MAIN,                          MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 148 */ { MAP_109_GI_FLOOR_3_BOILER_PLANT,                  MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 149 */ { MAP_10A_GI_FLOOR_3_PACKING_ROOM,                  MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 150 */ { MAP_10B_GI_FLOOR_4_MAIN,                          MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 151 */ { MAP_10C_GI_FLOOR_4_CABLE_ROOM,                    MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 152 */ { MAP_10D_GI_FLOOR_4_QUALITY_CONTROL,               MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 153 */ { MAP_10E_GI_FLOOR_5,                               MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 154 */ { MAP_10F_GI_BASEMENT_AIR_CON_PLANT,                MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 155 */ { MAP_110_GI_BASEMENT_BOSS_REPAIR_DEPOT,            MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 156 */ { MAP_111_GI_BASEMENT_WASTE_DISPOSAL,               MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 157 */ { MAP_11F_GI_WUMBAS_WIGWAM,                         MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 158 */ { MAP_172_GI_MUMBOS_SKULL,                          MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 159 */ { MAP_17D_GI_PACKING_GAME,                          MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 160 */ { MAP_162_GI_FLOOR_4_CLINKERS_CAVERN,               MUSIC_86_GI_CLINKERS,                   1, 0x00 },
/* 161 */ { MAP_187_GI_SEWER_ENTRANCE,                        MUSIC_3F_GI_MAIN,                       1, 0x2B },
/* 162 */ { MAP_127_HFP_LAVA_MAIN_AREA,                       MUSIC_41_HFP_MAIN,                      1, 0x2C },
/* 163 */ { MAP_128_HFP_ICY_MAIN_AREA,                        MUSIC_41_HFP_MAIN,                      1, 0x2F },
/* 164 */ { MAP_129_HFP_LAVA_TRAIN_STATION,                   MUSIC_41_HFP_MAIN,                      1, 0x2D },
/* 165 */ { MAP_12A_HFP_ICY_TRAIN_STATION,                    MUSIC_41_HFP_MAIN,                      1, 0x30 },
/* 166 */ { MAP_12B_HFP_LAVA_BOSS_CHILLI_BILLI,               MUSIC_41_HFP_MAIN,                      1, 0x2D },
/* 167 */ { MAP_12C_HFP_ICY_BOSS_CHILLY_WILLY,                MUSIC_41_HFP_MAIN,                      1, 0x30 },
/* 168 */ { MAP_12D_HFP_LAVA_KICKBALL_STADIUM_LOBBY,          MUSIC_41_HFP_MAIN,                      1, 0x2D },
/* 169 */ { MAP_131_HFP_ICY_BOGGYS_IGLOO,                     MUSIC_4D_HFP_BOGGYS_HOUSE,              1, 0x00 },
/* 170 */ { MAP_132_HFP_ICY_ICICLE_GROTTO,                    MUSIC_41_HFP_MAIN,                      1, 0x30 },
/* 171 */ { MAP_133_HFP_LAVA_INSIDE_THE_VOLCANO,              MUSIC_41_HFP_MAIN,                      1, 0x2D },
/* 172 */ { MAP_134_HFP_LAVA_MUMBOS_SKULL,                    MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 173 */ { MAP_135_HFP_ICY_WUMBAS_WIGWAM,                    MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 174 */ { MAP_180_HFP_LAVA_KICKBALL_ARENA,                  MUSIC_41_HFP_MAIN,                      0, 0x2D },
/* 175 */ { MAP_12E_HFP_LAVA_KICKBALL_STADIUM_1,              MUSIC_41_HFP_MAIN,                      0, 0x2D },
/* 176 */ { MAP_12F_HFP_LAVA_KICKBALL_STADIUM_2,              MUSIC_41_HFP_MAIN,                      0, 0x2D },
/* 177 */ { MAP_130_HFP_LAVA_KICKBALL_STADIUM_3,              MUSIC_41_HFP_MAIN,                      0, 0x2D },
/* 178 */ { MAP_136_CCL_MAIN_AREA,                            MUSIC_57_CCL_MAIN,                      1, 0x32 },
/* 179 */ { MAP_137_CCL_INSIDE_THE_TRASH_CAN,                 MUSIC_57_CCL_MAIN,                      1, 0x35 },
/* 180 */ { MAP_138_CCL_INSIDE_THE_CHEESE_WEDGE,              MUSIC_57_CCL_MAIN,                      1, 0x36 },
/* 181 */ { MAP_139_CCL_ZUBBAS_NEST,                          MUSIC_57_CCL_MAIN,                      1, 0x36 },
/* 182 */ { MAP_13A_CCL_CENTRAL_CAVERN,                       MUSIC_57_CCL_MAIN,                      1, 0x33 },
/* 183 */ { MAP_13D_CCL_INSIDE_THE_POT_O_GOLD,                MUSIC_57_CCL_MAIN,                      1, 0x34 },
/* 184 */ { MAP_13E_CCL_MUMBOS_SKULL,                         MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 185 */ { MAP_13F_CCL_BOSS_MINGY_JONGOS_SKULL,              MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 186 */ { MAP_140_CCL_WUMBAS_WIGWAM,                        MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 187 */ { MAP_185_CCL_TRASH_CAN_MINI,                       MUSIC_57_CCL_MAIN,                      1, 0x35 },
/* 188 */ { MAP_161_CCL_CANARY_MARY_RACE,                     MUSIC_57_CCL_MAIN,                      1, 0x32 },
/* 189 */ { MAP_188_MULTIPLAYER_CCL_ZUBBAS_NEST,              MUSIC_57_CCL_MAIN,                      1, 0x36 },
/* 190 */ { MAP_15D_CK_MAIN_AREA,                             MUSIC_75_CK_MAIN,                       1, 0x39 },
/* 191 */ { MAP_15E_CK_BOSS_THE_GATEHOUSE,                    MUSIC_75_CK_MAIN,                       1, 0x3A },
/* 192 */ { MAP_15F_CK_TOWER_OF_TRAGEDY,                      MUSIC_7E_CK_TOT,                        1, 0x00 },
/* 193 */ { MAP_160_CK_GUN_CHAMBER,                           MUSIC_75_CK_MAIN,                       1, 0x3A },
/* 194 */ { MAP_189_MULTIPLAYER_CK_TOWER_OF_TRAGEDY,          MUSIC_7E_CK_TOT,                        1, 0x00 },
/* 195 */ { MAP_18A_CK_INSIDE_HAG_1,                          MUSIC_75_CK_MAIN,                       1, 0x39 },
/* 196 */ { MAP_19A_CK_BOSS_HAG_1,                            MUSIC_75_CK_MAIN,                       1, 0x39 },
/* 197 */ { MAP_142_JV_MAIN_AREA,                             MUSIC_59_IOH_JV,                        1, 0x37 },
/* 198 */ { MAP_143_JV_BOTTLES_HOUSE,                         MUSIC_62_IOH_JV_BOTTLES_HOUSE,          0, 0x00 },
/* 199 */ { MAP_144_JV_KING_JINGALINGS_THRONE_ROOM,           MUSIC_5C_IOH_JV_THRONE,                 1, 0x00 },
/* 200 */ { MAP_19B_JV_JINGALINGS_ZOMBIFIED_THRONE_ROOM,      MUSIC_5D_IOH_JV_THRONE_ZOMBIE,          1, 0x00 },
/* 201 */ { MAP_145_JV_GREEN_JINJO_HOUSE,                     MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 202 */ { MAP_146_JV_BLACK_JINJO_HOUSE,                     MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 203 */ { MAP_147_JV_YELLOW_JINJO_HOUSE,                    MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 204 */ { MAP_148_JV_BLUE_JINJO_HOUSE,                      MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 205 */ { MAP_149_JV_UNUSED_JINJO_HOUSE,                    MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 206 */ { MAP_14A_JV_BROWN_JINJO_HOUSE,                     MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 207 */ { MAP_14B_JV_ORANGE_JINJO_HOUSE,                    MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 208 */ { MAP_14C_JV_PURPLE_JINJO_HOUSE,                    MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 209 */ { MAP_14D_JV_RED_JINJO_HOUSE,                       MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 210 */ { MAP_14E_JV_WHITE_JINJO_HOUSE,                     MUSIC_5A_IOH_JV_SAD_JINJOS,             1, 0x00 },
/* 211 */ { MAP_14F_IOH_WOODED_HOLLOW,                        MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 212 */ { MAP_152_IOH_PLATEAU,                              MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 213 */ { MAP_154_IOH_PINE_GROVE,                           MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 214 */ { MAP_155_IOH_CLIFF_TOP,                            MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 215 */ { MAP_15A_IOH_WASTELAND,                            MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 216 */ { MAP_15C_IOH_QUAGMIRE,                             MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 217 */ { MAP_150_IOH_HEGGYS_EGG_SHED,                      MUSIC_7F_IOH_HEGGY,                     0, 0x00 },
/* 218 */ { MAP_151_IOH_JIGGYWIGGYS_TEMPLE,                   MUSIC_5E_IOH_JIGGYWIGGY,                1, 0x00 },
/* 219 */ { MAP_153_IOH_HONEY_BS_HIVE,                        MUSIC_5F_IOH_HONEY_B,                   1, 0x00 },
/* 220 */ { MAP_157_IOH_WUMBAS_WIGWAM,                        MUSIC_37_WUMBAS_WIGWAM,                 0, 0x00 },
/* 221 */ { MAP_156_IOH_MUMBOS_SKULL,                         MUSIC_1A_MUMBOS_SKULL,                  0, 0x00 },
/* 222 */ { MAP_15B_IOH_BOSS_INSIDE_ANOTHER_DIGGER_TUNNEL,    MUSIC_32_SM_MAIN,                       1, 0x02 },
/* 223 */ { MAP_164_MULTIPLAYER_GI_CLINKERS_CAVERN,           MUSIC_86_GI_CLINKERS,                   1, 0x00 },
/* 224 */ { MAP_165_MULTIPLAYER_GGM_ORDNANCE_STORAGE,         MUSIC_85_GGM_ALTERNATE,                 0, 0x45 },
/* 225 */ { MAP_166_MULTIPLAYER_MT_TARGITZANS_TEMPLE,         MUSIC_39_MT_MAIN,                       1, 0x06 },
/* 226 */ { MAP_185_CCL_TRASH_CAN_MINI,                       MUSIC_57_CCL_MAIN,                      0, 0x35 },
/* 227 */ { _MAP_CHUFFY_WW,                                   MUSIC_40_WW_MAIN,                       1, 0x18 },
/* 228 */ { _MAP_CHUFFY_GGM,                                  MUSIC_3E_GGM_MAIN,                      1, 0x0C },
/* 229 */ { _MAP_CHUFFY_GI,                                   MUSIC_3F_GI_MAIN,                       1, 0x2A },
/* 230 */ { _MAP_CHUFFY_TDL,                                  MUSIC_52_TDL_MAIN,                      1, 0x26 },
/* 231 */ { _MAP_CHUFFY_IOH,                                  MUSIC_58_IOH_MAIN,                      1, 0x3B },
/* 232 */ { _MAP_CHUFFY_HFPL,                                 MUSIC_41_HFP_MAIN,                      1, 0x2D },
/* 233 */ { _MAP_CHUFFY_HFPI,                                 MUSIC_41_HFP_MAIN,                      1, 0x30 },
/* 234 */ { 0,                                                MUSIC_00_SELECT_MENU_OPTION_1,          0, 0x00 },
};

// TODO: arr01

/**
 * Used to play the theme of the world that the train is
 * currently in, while inside the train.
 */
struct
{
    /* enum MAP */
    s16 map1;
    /* enum MAP */
    s16 map2;
    /* enum FLAG */
    s16 flag;
}
themeOverrides[] =
{
/*  0 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_WW,     FLAG_4EE_STATION_TRAIN_PARKED_IN_WW   },
/*  1 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_GGM,    FLAG_4ED_STATION_TRAIN_PARKED_IN_GGM  },
/*  2 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_GI,     FLAG_4EF_STATION_TRAIN_PARKED_IN_GI   },
/*  3 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_TDL,    FLAG_4F0_STATION_TRAIN_PARKED_IN_TDL  },
/*  4 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_IOH,    FLAG_4F3_STATION_TRAIN_PARKED_IN_IoH  },
/*  5 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_HFPL,   FLAG_4F2_STATION_TRAIN_PARKED_IN_HFPL },
/*  6 */ { MAP_0D0_GGM_CHUFFYS_CAB,           _MAP_CHUFFY_HFPI,   FLAG_4F1_STATION_TRAIN_PARKED_IN_HFPI },
/*  7 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_WW,     FLAG_4EE_STATION_TRAIN_PARKED_IN_WW   },
/*  8 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_GGM,    FLAG_4ED_STATION_TRAIN_PARKED_IN_GGM  },
/*  9 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_GI,     FLAG_4EF_STATION_TRAIN_PARKED_IN_GI   },
/* 10 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_TDL,    FLAG_4F0_STATION_TRAIN_PARKED_IN_TDL  },
/* 11 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_IOH,    FLAG_4F3_STATION_TRAIN_PARKED_IN_IoH  },
/* 12 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_HFPL,   FLAG_4F2_STATION_TRAIN_PARKED_IN_HFPL },
/* 13 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,  _MAP_CHUFFY_HFPI,   FLAG_4F1_STATION_TRAIN_PARKED_IN_HFPI },
/* 14 */ { 0,                                  0,                 0                                     },               
};


s32 DLL_cothemedll_00(MAP a0)
{
    s32 i;
    s32 map = a0; //? Yep

    //- Check for music overrides
    for (i = 0; themeOverrides[i].map1; i++)
        if (map == themeOverrides[i].map1 && fn_flag_get(themeOverrides[i].flag))
            map =  themeOverrides[i].map2;

    //- Return the index of the theme for this map
    for (i = 0; themes[i].map; i++)
        if (map == themes[i].map)
            return i;

    return 0;
}

void DLL_cothemedll_01(MAP map)
{

}

s32 DLL_cothemedll_02(MAP map)
{
    return themes[DLL_cothemedll_00(map)].instrumentSet;
}

void DLL_cothemedll_03(s32 a0, MAP map)
{

}

// musicObj * (?)
void DLL_cothemedll_04(void *m)
{

}

/*static*/ void fn_priv_00(MAP map)
{
    switch (gsWorldGetSection())
    {
        case MAP_0B8_MT_MAIN_AREA:
        case MAP_0BB_MT_MAYAN_KICKBALL_STADIUM_LOBBY:
        case MAP_0C6_MT_KICKBALL_ARENA_1:
        case MAP_0C8_MT_KICKBALL_ARENA_2:
        case MAP_0C9_MT_KICKBALL_ARENA_3:
        {
            switch (map)
            {
                case MAP_0B8_MT_MAIN_AREA:
                case MAP_0BB_MT_MAYAN_KICKBALL_STADIUM_LOBBY:
                case MAP_0C6_MT_KICKBALL_ARENA_1:
                case MAP_0C8_MT_KICKBALL_ARENA_2:
                case MAP_0C9_MT_KICKBALL_ARENA_3:
                    fn_flag_set_675_TRUE();
                    break;
            }
            break;
        }
        case MAP_127_HFP_LAVA_MAIN_AREA:
        case MAP_12D_HFP_LAVA_KICKBALL_STADIUM_LOBBY:
        case MAP_12E_HFP_LAVA_KICKBALL_STADIUM_1:
        case MAP_12F_HFP_LAVA_KICKBALL_STADIUM_2:
        case MAP_130_HFP_LAVA_KICKBALL_STADIUM_3:
        {
            switch (map)
            {
                case MAP_127_HFP_LAVA_MAIN_AREA:
                case MAP_12D_HFP_LAVA_KICKBALL_STADIUM_LOBBY:
                case MAP_12E_HFP_LAVA_KICKBALL_STADIUM_1:
                case MAP_12F_HFP_LAVA_KICKBALL_STADIUM_2:
                case MAP_130_HFP_LAVA_KICKBALL_STADIUM_3:
                    fn_flag_set_675_TRUE();
                    break;
            }
            break;
        }
    }
}

void DLL_cothemedll_05(void *m, MAP max)
{

}

/*static*/ void fn_priv_01(s32 a0, s32 a1)
{

}

void DLL_cothemedll_06(s32 a0, s32 a1, s32 a2)
{

}
























