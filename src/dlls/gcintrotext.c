#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"

#include "include/enum/map.h"
#include "include/enum/flag.h"
#include "include/enum/asset.h"


// forward decl
static struct struct00 *fn_priv_00(MAP);
static bool             fn_priv_01(MAP);



void DLL_gcintrotext_00(void)
{
    fn_flag_set_TRUE(FLAG2_UNK_6CB);
}

bool DLL_gcintrotext_01(void)
{
    //? Yeah they really wrote it like this apparently

    if (fn_flag_get_and_set(FLAG2_UNK_6CB, FALSE))
        return TRUE;

    return FALSE;
}

struct struct00
{
    /* enum MAP */
    u32 map        : 10;
    /* enum ASSET */
    u32 asset      : 16;
    /**
     * The index of the introtext for the specific map inside the
     * asset for the whole level.
     */
    u32 idxInAsset : 6;
};

static struct struct00
arr00[] =
{
/* dec */
/*   0 */ { MAP_0A1_CUTSCENE_TWO_YEARS_HAVE_PASSED,           ASSET_INTROTEXT_SM_1,        0  },
/*   1 */ { MAP_0A2_CUTSCENE_HAG_1_ARRIVES,                   ASSET_INTROTEXT_SM_1,        0  },
/*   2 */ { MAP_0A3_CUTSCENE_SISTERS_ARRIVE,                  ASSET_INTROTEXT_SM_1,        0  },
/*   3 */ { MAP_0A4_CUTSCENE_GRUNTILDA_REVIVED,               ASSET_INTROTEXT_SM_1,        0  },
/*   4 */ { MAP_0A5_CUTSCENE_GRUNTILDA_SPELL,                 ASSET_INTROTEXT_SM_1,        0  },
/*   5 */ { MAP_0A6_CUTSCENE_HAG_1_LEAVES,                    ASSET_INTROTEXT_SM_1,        0  },
/*   6 */ { MAP_0A7_CUTSCENE_BANJO_VOW,                       ASSET_INTROTEXT_SM_1,        0  },
/*   7 */ { MAP_18B_INTRO_SCREEN,                             ASSET_INTROTEXT_SM_1,        0  },
/*   8 */ { MAP_0A8_CUTSCENE_PLAYING_POKER,                   ASSET_INTROTEXT_SM_1,        1  },
/*   9 */ { MAP_0A9_CUTSCENE_EARTHQUAKE,                      ASSET_INTROTEXT_SM_1,        1  },
/*  10 */ { MAP_0AA_CUTSCENE_MUMBO_LOOK_OUTSIDE,              ASSET_INTROTEXT_SM_1,        1  },
/*  11 */ { MAP_0AB_CUTSCENE_MUMBO_WARN,                      ASSET_INTROTEXT_SM_1,        1  },
/*  12 */ { MAP_0AC_CUTSCENE_BANJO_HOUSE_DESTROYED,           ASSET_INTROTEXT_SM_1,        1  },
/*  13 */ { MAP_0AF_SM_MAIN_AREA,                             ASSET_INTROTEXT_SM_1,        0  },
/*  14 */ { MAP_173_SM_BANJOS_HOUSE,                          ASSET_INTROTEXT_SM_1,        1  },
/*  15 */ { MAP_0AE_SM_BEHIND_THE_WATERFALL,                  ASSET_INTROTEXT_SM_2,        0  },
/*  16 */ { MAP_0AD_SM_GRUNTYS_LAIR,                          ASSET_INTROTEXT_SM_2,        1  },
/*  17 */ { MAP_141_SM_BOSS_INSIDE_THE_DIGGER_TUNNEL,         ASSET_INTROTEXT_SM_1,        2  },
/*  18 */ { MAP_0B6_MT_WUMBAS_WIGWAM,                         ASSET_INTROTEXT_SHAMANS,     1  },
/*  19 */ { MAP_0B7_MT_MUMBOS_SKULL,                          ASSET_INTROTEXT_SHAMANS,     0  },
/*  20 */ { MAP_0B8_MT_MAIN_AREA,                             ASSET_INTROTEXT_MT,          0  },
/*  21 */ { MAP_0B9_MT_PRISON_COMPOUND,                       ASSET_INTROTEXT_MT,          5  },
/*  22 */ { MAP_0BA_MT_COLUMNS_VAULT,                         ASSET_INTROTEXT_MT,          1  },
/*  23 */ { MAP_0BB_MT_MAYAN_KICKBALL_STADIUM_LOBBY,          ASSET_INTROTEXT_MT,          3  },
/*  24 */ { MAP_0BC_MT_CODE_CHAMBER,                          ASSET_INTROTEXT_MT,          4  },
/*  25 */ { MAP_0C4_MT_JADE_SNAKE_GROVE,                      ASSET_INTROTEXT_MT,          14 },
/*  26 */ { MAP_0C5_MT_TREASURE_CHAMBER,                      ASSET_INTROTEXT_MT,          2  },
/*  27 */ { MAP_0C6_MT_KICKBALL_ARENA_1,                      ASSET_INTROTEXT_MT,          6  },
/*  28 */ { MAP_0C8_MT_KICKBALL_ARENA_2,                      ASSET_INTROTEXT_MT,          7  },
/*  29 */ { MAP_0C9_MT_KICKBALL_ARENA_3,                      ASSET_INTROTEXT_MT,          8  },
/*  30 */ { MAP_177_MT_TARGITZANS_SLIGHTLY_SACRED_CHAMBER,    ASSET_INTROTEXT_MT,          9  },
/*  31 */ { MAP_17A_MT_BOSS_TARGITZANS_REALLY_SACRED_CHAMBER, ASSET_INTROTEXT_MT,          10 },
/*  32 */ { MAP_178_MT_TARGITZANS_TEMPLE,                     ASSET_INTROTEXT_MT,          12 },
/*  33 */ { MAP_179_MT_TARGITZANS_TEMPLE_LOBBY,               ASSET_INTROTEXT_MT,          11 },
/*  34 */ { MAP_0C7_GGM_MAIN_AREA,                            ASSET_INTROTEXT_GGM,         0  },
/*  35 */ { MAP_0CA_GGM_FUEL_DEPOT,                           ASSET_INTROTEXT_GGM,         14 },
/*  36 */ { MAP_0CB_GGM_CRUSHING_SHED,                        ASSET_INTROTEXT_GGM,         1  },
/*  37 */ { MAP_0CC_GGM_FLOODED_CAVES,                        ASSET_INTROTEXT_GGM,         2  },
/*  38 */ { MAP_0CD_GGM_WATER_STORAGE,                        ASSET_INTROTEXT_GGM,         3  },
/*  39 */ { MAP_0CE_GGM_WATERFALL_CAVERN,                     ASSET_INTROTEXT_GGM,         4  },
/*  40 */ { MAP_0CF_GGM_POWER_HUT_BASEMENT,                   ASSET_INTROTEXT_GGM,         5  },
/*  41 */ { MAP_0D0_GGM_CHUFFYS_CAB,                          ASSET_INTROTEXT_GGM,         12 },
/*  42 */ { MAP_0D1_GGM_BOSS_INSIDE_CHUFFYS_BOILER,           ASSET_INTROTEXT_GGM,         11 },
/*  43 */ { MAP_0D2_GGM_GLOOMY_CAVERNS,                       ASSET_INTROTEXT_GGM,         7  },
/*  44 */ { MAP_0D3_GGM_GENERATOR_CAVERN,                     ASSET_INTROTEXT_GGM,         8  },
/*  45 */ { MAP_0D4_GGM_POWER_HUT,                            ASSET_INTROTEXT_GGM,         9  },
/*  46 */ { MAP_0D7_GGM_TRAIN_STATION,                        ASSET_INTROTEXT_GGM,         10 },
/*  47 */ { MAP_0D8_GGM_PROSPECTORS_HUT,                      ASSET_INTROTEXT_GGM,         6  },
/*  48 */ { MAP_0DA_GGM_TOXIC_GAS_CAVE,                       ASSET_INTROTEXT_GGM,         15 },
/*  49 */ { MAP_0DB_GGM_CANARY_CAVE,                          ASSET_INTROTEXT_GGM,         16 },
/*  50 */ { MAP_0D9_GGM_MUMBOS_SKULL,                         ASSET_INTROTEXT_SHAMANS,     0  },
/*  51 */ { MAP_0DC_GGM_ORDNANCE_STORAGE,                     ASSET_INTROTEXT_GGM,         17 },
/*  52 */ { MAP_0E9_GGM_WUMBAS_WIGWAM,                        ASSET_INTROTEXT_SHAMANS,     1  },
/*  53 */ { MAP_121_GGM_INSIDE_CHUFFYS_WAGON,                 ASSET_INTROTEXT_GGM,         13 },
/*  54 */ { MAP_163_GGM_ORDNANCE_STORAGE_ENTRANCE,            ASSET_INTROTEXT_GGM,         18 },
/*  55 */ { MAP_0D6_WW_MAIN_AREA,                             ASSET_INTROTEXT_WW,          0  },
/*  56 */ { MAP_124_WW_SAUCER_OF_PERIL,                       ASSET_INTROTEXT_WW,          21 },
/*  57 */ { MAP_0D5_WW_WUMBAS_WIGWAM,                         ASSET_INTROTEXT_SHAMANS,     1  },
/*  58 */ { MAP_0DD_WW_DODGEM_DOME_LOBBY,                     ASSET_INTROTEXT_WW,          1  },
/*  59 */ { MAP_0DE_WW_DODGEM_CHALLENGE_1V1,                  ASSET_INTROTEXT_WW,          13 },
/*  60 */ { MAP_0DF_WW_DODGEM_CHALLENGE_2V1,                  ASSET_INTROTEXT_WW,          14 },
/*  61 */ { MAP_0E0_WW_DODGEM_CHALLENGE_3V1,                  ASSET_INTROTEXT_WW,          15 },
/*  62 */ { MAP_0E1_WW_CRAZY_CASTLE_STOCKADE,                 ASSET_INTROTEXT_WW,          2  },
/*  63 */ { MAP_13B_WW_CRAZY_CASTLE_STOCKADE_SAUCER,          ASSET_INTROTEXT_WW,          22 },
/*  64 */ { MAP_0E2_WW_CRAZY_CASTLE_LOBBY,                    ASSET_INTROTEXT_WW,          3  },
/*  65 */ { MAP_0E3_WW_CRAZY_CASTLE_PUMP_ROOM,                ASSET_INTROTEXT_WW,          4  },
/*  66 */ { MAP_0E4_WW_BALLOON_BURST_GAME,                    ASSET_INTROTEXT_WW,          10 },
/*  67 */ { MAP_0E5_WW_HOOP_HURRY,                            ASSET_INTROTEXT_WW,          11 },
/*  68 */ { MAP_0E6_WW_STAR_SPINNER,                          ASSET_INTROTEXT_WW,          5  },
/*  69 */ { MAP_13C_WW_STAR_SPINNER_SAUCER,                   ASSET_INTROTEXT_WW,          23 },
/*  70 */ { MAP_0E7_WW_THE_INFERNO,                           ASSET_INTROTEXT_WW,          6  },
/*  71 */ { MAP_0EA_WW_CAVE_OF_HORRORS,                       ASSET_INTROTEXT_WW,          7  },
/*  72 */ { MAP_0EB_WW_HAUNTED_CAVERN,                        ASSET_INTROTEXT_WW,          8  },
/*  73 */ { MAP_0EC_WW_TRAIN_STATION,                         ASSET_INTROTEXT_WW,          9  },
/*  74 */ { MAP_0F9_WW_BOSS_MR_PATCH,                         ASSET_INTROTEXT_WW,          12 },
/*  75 */ { MAP_176_WW_MUMBOS_SKULL,                          ASSET_INTROTEXT_SHAMANS,     0  },
/*  76 */ { MAP_1A7_JRL_MAIN_AREA,                            ASSET_INTROTEXT_JRL,         0  },
/*  77 */ { MAP_1A6_JRL_SMUGGLERS_CAVERN,                     ASSET_INTROTEXT_JRL,         16 },
/*  78 */ { MAP_1A8_JRL_ATLANTIS,                             ASSET_INTROTEXT_JRL,         14 },
/*  79 */ { MAP_1A9_JRL_SEA_BOTTOM,                           ASSET_INTROTEXT_JRL,         15 },
/*  80 */ { MAP_0EF_JRL_MUMBOS_SKULL,                         ASSET_INTROTEXT_SHAMANS,     0  },
/*  81 */ { MAP_0ED_JRL_JOLLYS,                               ASSET_INTROTEXT_JRL,         1  },
/*  82 */ { MAP_0EE_JRL_PAWNOS_EMPORIUM,                      ASSET_INTROTEXT_JRL,         2  },
/*  83 */ { MAP_0F1_JRL_INSIDE_THE_UFO,                       ASSET_INTROTEXT_JRL,         3  },
/*  84 */ { MAP_0F4_JRL_ANCIENT_SWIMMING_BATHS,               ASSET_INTROTEXT_JRL,         11 },
/*  85 */ { MAP_0F6_JRL_ELECTRIC_EELS_LAIR,                   ASSET_INTROTEXT_JRL,         12 },
/*  86 */ { MAP_0F7_JRL_SEAWEED_SANCTUM,                      ASSET_INTROTEXT_JRL,         4  },
/*  87 */ { MAP_0F8_JRL_INSIDE_THE_BIG_FISH,                  ASSET_INTROTEXT_JRL,         5  },
/*  88 */ { MAP_0FA_JRL_TEMPLE_OF_THE_FISHES,                 ASSET_INTROTEXT_JRL,         6  },
/*  89 */ { MAP_0FC_JRL_BOSS_LORD_WOO_FAK_FAK,                ASSET_INTROTEXT_JRL,         13 },
/*  90 */ { MAP_0FF_JRL_BLUBBERS_WAVE_RACE_HIRE,              ASSET_INTROTEXT_JRL,         7  },
/*  91 */ { MAP_120_JRL_WUMBAS_WIGWAM,                        ASSET_INTROTEXT_SHAMANS,     1  },
/*  92 */ { MAP_126_GGM_WATER_SUPPLY_PIPE,                    ASSET_INTROTEXT_JRL,         8  },
/*  93 */ { MAP_125_GI_WATER_SUPPLY_PIPE,                     ASSET_INTROTEXT_JRL,         9  },
/*  94 */ { MAP_181_JRL_SEA_BOTTOM_CAVERN,                    ASSET_INTROTEXT_JRL,         10 },
/*  95 */ { MAP_112_TDL_MAIN_AREA,                            ASSET_INTROTEXT_TDL,         0  },
/*  96 */ { MAP_113_TDL_BOSS_TERRYS_NEST,                     ASSET_INTROTEXT_TDL,         1  },
/*  97 */ { MAP_114_TDL_TRAIN_STATION,                        ASSET_INTROTEXT_TDL,         2  },
/*  98 */ { MAP_115_TDL_OOGLE_BOOGLES_CAVE,                   ASSET_INTROTEXT_TDL,         3  },
/*  99 */ { MAP_116_TDL_INSIDE_THE_MOUNTAIN,                  ASSET_INTROTEXT_TDL,         4  },
/* 100 */ { MAP_117_TDL_RIVER_PASSAGE,                        ASSET_INTROTEXT_TDL,         5  },
/* 101 */ { MAP_118_TDL_STYRACOSAURUS_FAMILY_CAVE,            ASSET_INTROTEXT_TDL,         6  },
/* 102 */ { MAP_119_TDL_UNGA_BUNGAS_CAVE,                     ASSET_INTROTEXT_TDL,         7  },
/* 103 */ { MAP_11A_TDL_STOMPING_PLAINS,                      ASSET_INTROTEXT_TDL,         11 },
/* 104 */ { MAP_11B_TDL_BONFIRE_CAVERN,                       ASSET_INTROTEXT_TDL,         8  },
/* 105 */ { MAP_11E_TDL_WUMBAS_WIGWAM_SMALL,                  ASSET_INTROTEXT_SHAMANS,     1  },
/* 106 */ { MAP_122_TDL_WUMBAS_WIGWAM_BIG,                    ASSET_INTROTEXT_SHAMANS,     1  },
/* 107 */ { MAP_123_TDL_INSIDE_CHOMPAS_BELLY,                 ASSET_INTROTEXT_TDL,         10 },
/* 108 */ { MAP_171_TDL_MUMBOS_SKULL,                         ASSET_INTROTEXT_SHAMANS,     0  },
/* 109 */ { MAP_100_GI_MAIN_AREA,                             ASSET_INTROTEXT_GI,          0  },
/* 110 */ { MAP_101_GI_FLOOR_1,                               ASSET_INTROTEXT_GI,          1  },
/* 111 */ { MAP_102_GI_TRAIN_STATION,                         ASSET_INTROTEXT_GI,          2  },
/* 112 */ { MAP_103_GI_WORKERS_QUARTERS,                      ASSET_INTROTEXT_GI,          3  },
/* 113 */ { MAP_104_GI_TRASH_COMPACTOR,                       ASSET_INTROTEXT_GI,          4  },
/* 114 */ { MAP_105_GI_ELEVATOR_SHAFT,                        ASSET_INTROTEXT_GI,          5  },
/* 115 */ { MAP_106_GI_FLOOR_2_MAIN,                          ASSET_INTROTEXT_GI,          6  },
/* 116 */ { MAP_107_GI_FLOOR_2_ELECTROMAGNET_CHAMBER,         ASSET_INTROTEXT_GI,          7  },
/* 117 */ { MAP_108_GI_FLOOR_3_MAIN,                          ASSET_INTROTEXT_GI,          8  },
/* 118 */ { MAP_109_GI_FLOOR_3_BOILER_PLANT,                  ASSET_INTROTEXT_GI,          9  },
/* 119 */ { MAP_10A_GI_FLOOR_3_PACKING_ROOM,                  ASSET_INTROTEXT_GI,          16 },
/* 120 */ { MAP_10B_GI_FLOOR_4_MAIN,                          ASSET_INTROTEXT_GI,          10 },
/* 121 */ { MAP_10C_GI_FLOOR_4_CABLE_ROOM,                    ASSET_INTROTEXT_GI,          11 },
/* 122 */ { MAP_10D_GI_FLOOR_4_QUALITY_CONTROL,               ASSET_INTROTEXT_GI,          12 },
/* 123 */ { MAP_10E_GI_FLOOR_5,                               ASSET_INTROTEXT_GI,          13 },
/* 124 */ { MAP_10F_GI_BASEMENT_AIR_CON_PLANT,                ASSET_INTROTEXT_GI,          14 },
/* 125 */ { MAP_110_GI_BASEMENT_BOSS_REPAIR_DEPOT,            ASSET_INTROTEXT_GI,          17 },
/* 126 */ { MAP_111_GI_BASEMENT_WASTE_DISPOSAL,               ASSET_INTROTEXT_GI,          15 },
/* 127 */ { MAP_11F_GI_WUMBAS_WIGWAM,                         ASSET_INTROTEXT_SHAMANS,     1  },
/* 128 */ { MAP_172_GI_MUMBOS_SKULL,                          ASSET_INTROTEXT_SHAMANS,     0  },
/* 129 */ { MAP_162_GI_FLOOR_4_CLINKERS_CAVERN,               ASSET_INTROTEXT_GI,          19 },
/* 130 */ { MAP_187_GI_SEWER_ENTRANCE,                        ASSET_INTROTEXT_GI,          20 },
/* 131 */ { MAP_127_HFP_LAVA_MAIN_AREA,                       ASSET_INTROTEXT_HFP,         0  },
/* 132 */ { MAP_128_HFP_ICY_MAIN_AREA,                        ASSET_INTROTEXT_HFP,         1  },
/* 133 */ { MAP_129_HFP_LAVA_TRAIN_STATION,                   ASSET_INTROTEXT_HFP,         2  },
/* 134 */ { MAP_12A_HFP_ICY_TRAIN_STATION,                    ASSET_INTROTEXT_HFP,         3  },
/* 135 */ { MAP_12B_HFP_LAVA_BOSS_CHILLI_BILLI,               ASSET_INTROTEXT_HFP,         4  },
/* 136 */ { MAP_12C_HFP_ICY_BOSS_CHILLY_WILLY,                ASSET_INTROTEXT_HFP,         5  },
/* 137 */ { MAP_12D_HFP_LAVA_KICKBALL_STADIUM_LOBBY,          ASSET_INTROTEXT_HFP,         6  },
/* 138 */ { MAP_12E_HFP_LAVA_KICKBALL_STADIUM_1,              ASSET_INTROTEXT_HFP,         10 },
/* 139 */ { MAP_12F_HFP_LAVA_KICKBALL_STADIUM_2,              ASSET_INTROTEXT_HFP,         11 },
/* 140 */ { MAP_130_HFP_LAVA_KICKBALL_STADIUM_3,              ASSET_INTROTEXT_HFP,         12 },
/* 141 */ { MAP_131_HFP_ICY_BOGGYS_IGLOO,                     ASSET_INTROTEXT_HFP,         7  },
/* 142 */ { MAP_132_HFP_ICY_ICICLE_GROTTO,                    ASSET_INTROTEXT_HFP,         8  },
/* 143 */ { MAP_133_HFP_LAVA_INSIDE_THE_VOLCANO,              ASSET_INTROTEXT_HFP,         9  },
/* 144 */ { MAP_134_HFP_LAVA_MUMBOS_SKULL,                    ASSET_INTROTEXT_SHAMANS,     0  },
/* 145 */ { MAP_135_HFP_ICY_WUMBAS_WIGWAM,                    ASSET_INTROTEXT_SHAMANS,     1  },
/* 146 */ { MAP_136_CCL_MAIN_AREA,                            ASSET_INTROTEXT_CCL,         0  },
/* 147 */ { MAP_137_CCL_INSIDE_THE_TRASH_CAN,                 ASSET_INTROTEXT_CCL,         1  },
/* 148 */ { MAP_138_CCL_INSIDE_THE_CHEESE_WEDGE,              ASSET_INTROTEXT_CCL,         2  },
/* 149 */ { MAP_139_CCL_ZUBBAS_NEST,                          ASSET_INTROTEXT_CCL,         3  },
/* 150 */ { MAP_13A_CCL_CENTRAL_CAVERN,                       ASSET_INTROTEXT_CCL,         4  },
/* 151 */ { MAP_13D_CCL_INSIDE_THE_POT_O_GOLD,                ASSET_INTROTEXT_CCL,         6  },
/* 152 */ { MAP_13E_CCL_MUMBOS_SKULL,                         ASSET_INTROTEXT_SHAMANS,     0  },
/* 153 */ { MAP_13F_CCL_BOSS_MINGY_JONGOS_SKULL,              ASSET_INTROTEXT_SHAMANS,     0  },
/* 154 */ { MAP_140_CCL_WUMBAS_WIGWAM,                        ASSET_INTROTEXT_SHAMANS,     1  },
/* 155 */ { MAP_15D_CK_MAIN_AREA,                             ASSET_INTROTEXT_CK,          0  },
/* 156 */ { MAP_15E_CK_BOSS_THE_GATEHOUSE,                    ASSET_INTROTEXT_CK,          1  },
/* 157 */ { MAP_15F_CK_TOWER_OF_TRAGEDY,                      ASSET_INTROTEXT_CK,          2  },
/* 158 */ { MAP_160_CK_GUN_CHAMBER,                           ASSET_INTROTEXT_CK,          3  },
/* 159 */ { MAP_18A_CK_INSIDE_HAG_1,                          ASSET_INTROTEXT_CK,          4  },
/* 160 */ { MAP_142_JV_MAIN_AREA,                             ASSET_INTROTEXT_IOH,         0  },
/* 161 */ { MAP_143_JV_BOTTLES_HOUSE,                         ASSET_INTROTEXT_IOH,         1  },
/* 162 */ { MAP_144_JV_KING_JINGALINGS_THRONE_ROOM,           ASSET_INTROTEXT_IOH,         2  },
/* 163 */ { MAP_19B_JV_JINGALINGS_ZOMBIFIED_THRONE_ROOM,      ASSET_INTROTEXT_IOH,         23 },
/* 164 */ { MAP_145_JV_GREEN_JINJO_HOUSE,                     ASSET_INTROTEXT_IOH,         3  },
/* 165 */ { MAP_146_JV_BLACK_JINJO_HOUSE,                     ASSET_INTROTEXT_IOH,         4  },
/* 166 */ { MAP_147_JV_YELLOW_JINJO_HOUSE,                    ASSET_INTROTEXT_IOH,         5  },
/* 167 */ { MAP_148_JV_BLUE_JINJO_HOUSE,                      ASSET_INTROTEXT_IOH,         6  },
/* 168 */ { MAP_JV_0x0149_UNUSED_JINJO_HOUSE,                 ASSET_INTROTEXT_IOH,         7  },
/* 169 */ { MAP_14A_JV_BROWN_JINJO_HOUSE,                     ASSET_INTROTEXT_IOH,         8  },
/* 170 */ { MAP_14B_JV_ORANGE_JINJO_HOUSE,                    ASSET_INTROTEXT_IOH,         9  },
/* 171 */ { MAP_14C_JV_PURPLE_JINJO_HOUSE,                    ASSET_INTROTEXT_IOH,         10 },
/* 172 */ { MAP_14D_JV_RED_JINJO_HOUSE,                       ASSET_INTROTEXT_IOH,         11 },
/* 173 */ { MAP_14E_JV_WHITE_JINJO_HOUSE,                     ASSET_INTROTEXT_IOH,         12 },
/* 174 */ { MAP_14F_IOH_WOODED_HOLLOW,                        ASSET_INTROTEXT_IOH,         17 },
/* 175 */ { MAP_150_IOH_HEGGYS_EGG_SHED,                      ASSET_INTROTEXT_IOH,         13 },
/* 176 */ { MAP_151_IOH_JIGGYWIGGYS_TEMPLE,                   ASSET_INTROTEXT_IOH,         14 },
/* 177 */ { MAP_152_IOH_PLATEAU,                              ASSET_INTROTEXT_IOH,         18 },
/* 178 */ { MAP_153_IOH_HONEY_BS_HIVE,                        ASSET_INTROTEXT_IOH,         15 },
/* 179 */ { MAP_154_IOH_PINE_GROVE,                           ASSET_INTROTEXT_IOH,         19 },
/* 180 */ { MAP_157_IOH_WUMBAS_WIGWAM,                        ASSET_INTROTEXT_SHAMANS,     1  },
/* 181 */ { MAP_155_IOH_CLIFF_TOP,                            ASSET_INTROTEXT_IOH,         20 },
/* 182 */ { MAP_156_IOH_MUMBOS_SKULL,                         ASSET_INTROTEXT_SHAMANS,     0  },
/* 183 */ { MAP_15A_IOH_WASTELAND,                            ASSET_INTROTEXT_IOH,         21 },
/* 184 */ { MAP_15B_IOH_BOSS_INSIDE_ANOTHER_DIGGER_TUNNEL,    ASSET_INTROTEXT_IOH,         16 },
/* 185 */ { MAP_15C_IOH_QUAGMIRE,                             ASSET_INTROTEXT_IOH,         22 },
/* 186 */ { MAP_17F_MT_KICKBALL_ARENA_4,                      ASSET_INTROTEXT_MULTIPLAYER, 0  },
/* 187 */ { MAP_166_MULTIPLAYER_MT_TARGITZANS_TEMPLE,         ASSET_INTROTEXT_MULTIPLAYER, 1  },
/* 188 */ { MAP_165_MULTIPLAYER_GGM_ORDNANCE_STORAGE,         ASSET_INTROTEXT_MULTIPLAYER, 2  },
/* 189 */ { MAP_186_WW_DODGEMS,                               ASSET_INTROTEXT_MULTIPLAYER, 3  },
/* 190 */ { MAP_17B_MULTIPLAYER_WW_BALLOON_BURST,             ASSET_INTROTEXT_MULTIPLAYER, 4  },
/* 191 */ { MAP_17C_MULTIPLAYER_WW_JUMP_THE_HOOPS,            ASSET_INTROTEXT_MULTIPLAYER, 5  },
/* 192 */ { MAP_182_MULTIPLAYER_JRL_SUBMARINE,                ASSET_INTROTEXT_MULTIPLAYER, 6  },
/* 193 */ { MAP_183_MULTIPLAYER_TDL_CHOMPAS_BELLY,            ASSET_INTROTEXT_MULTIPLAYER, 7  },
/* 194 */ { MAP_17D_GI_PACKING_GAME,                          ASSET_INTROTEXT_MULTIPLAYER, 8  },
/* 195 */ { MAP_164_MULTIPLAYER_GI_CLINKERS_CAVERN,           ASSET_INTROTEXT_MULTIPLAYER, 9  },
/* 196 */ { MAP_180_HFP_LAVA_KICKBALL_ARENA,                  ASSET_INTROTEXT_MULTIPLAYER, 10 },
/* 197 */ { MAP_185_CCL_TRASH_CAN_MINI,                       ASSET_INTROTEXT_MULTIPLAYER, 11 },
/* 198 */ { MAP_188_MULTIPLAYER_CCL_ZUBBAS_NEST,              ASSET_INTROTEXT_MULTIPLAYER, 12 },
};

struct struct01
{
    u32 _;
};

static struct struct01
arr01[] =
{
    0
};


s32 DLL_gcintrotext_02(MAP map, u32 *a1, u32 *a2)
{
    struct struct00 *s00;

    if (map == -1)
        map = gsWorldGetSection();

    s00 = fn_priv_00(map);

    if (s00 == NULL)
        return -1;

    *a1 = s00->asset;
    *a2 = s00->idxInAsset;

    return fn_priv_01(map);
}

/*static*/ struct struct00 *fn_priv_00(MAP map)
{
    s32 i;

    for (i = 0; i < ARRLEN(arr00); i++)
        if (map == arr00[i].map)
            return &arr00[i];

    return NULL;
}

static bool fn_priv_01(MAP map)
{
    return FALSE;
}










