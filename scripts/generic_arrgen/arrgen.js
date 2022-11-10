const fs = require("fs");


function ERROR(msg)
{
    console.error(`[ERROR]: ${msg}`);
    process.exit(1);
}

function FATAL(msg)
{
    console.error(`[FATAL]: ${msg}`);
    process.exit(1);
}



/**
 * Takes a value e.g. 1a7, and turns it into a "good value" e.g. "MAP_1A7_JRL_MAIN_AREA"
 * @param {number} val number to de-hardcode
 * @param {string} type
 * @param {number} base
 * @returns {string}
 */
function dehardcode_val(val, { type=undefined, base=16, prepadwidth=0 }={})
{

    //- Handled custom types will RETURN HERE
    switch (type)
    {
        case "MAP":
        {
            // start: 0x00A0
            let MAP =
            [
                "MAP_0A0_MIN",

                /*// 0x0001 - 0x00A0 unused (leftover from Banjo-Kazooie?)*/
                /* 0x00A1 */ "MAP_0A1_CUTSCENE_TWO_YEARS_HAVE_PASSED", /* exit 0 */
                /* 0x00A2 */ "MAP_0A2_CUTSCENE_HAG_1_ARRIVES", /* exit 1 */
                /* 0x00A3 */ "MAP_0A3_CUTSCENE_SISTERS_ARRIVE",
                /* 0x00A4 */ "MAP_0A4_CUTSCENE_GRUNTILDA_REVIVED",
                /* 0x00A5 */ "MAP_0A5_CUTSCENE_GRUNTILDA_SPELL",
                /* 0x00A6 */ "MAP_0A6_CUTSCENE_HAG_1_LEAVES",
                /* 0x00A7 */ "MAP_0A7_CUTSCENE_BANJO_VOW",
                /* 0x00A8 */ "MAP_0A8_CUTSCENE_PLAYING_POKER", /* exit 1 */
                /* 0x00A9 */ "MAP_0A9_CUTSCENE_EARTHQUAKE",
                /* 0x00AA */ "MAP_0AA_CUTSCENE_MUMBO_LOOK_OUTSIDE",
                /* 0x00AB */ "MAP_0AB_CUTSCENE_MUMBO_WARN",
                /* 0x00AC */ "MAP_0AC_CUTSCENE_BANJO_HOUSE_DESTROYED",
                /* 0x00AD */ "MAP_0AD_SM_GRUNTYS_LAIR",
                /* 0x00AE */ "MAP_0AE_SM_BEHIND_THE_WATERFALL",
                /* 0x00AF */ "MAP_0AF_SM_MAIN_AREA",
                /* 0x00B0 >>> */ "MAP_0x00B0_CRASH",
                /* 0x00B1 >>> */ "MAP_0x00B1_CRASH",
                /* 0x00B2 >>> */ "MAP_0x00B2_CRASH",
                /* 0x00B3 >>> */ "MAP_0x00B3_CRASH",
                /* 0x00B4 >>> */ "MAP_0x00B4_CRASH",
                /* 0x00B5 >>> */ "MAP_0x00B5_CRASH",
                /* 0x00B6 */ "MAP_0B6_MT_WUMBAS_WIGWAM",
                /* 0x00B7 */ "MAP_0B7_MT_MUMBOS_SKULL",
                /* 0x00B8 */ "MAP_0B8_MT_MAIN_AREA",
                /* 0x00B9 */ "MAP_0B9_MT_PRISON_COMPOUND",
                /* 0x00BA */ "MAP_0BA_MT_COLUMNS_VAULT",
                /* 0x00BB */ "MAP_0BB_MT_MAYAN_KICKBALL_STADIUM_LOBBY",
                /* 0x00BC */ "MAP_0BC_MT_CODE_CHAMBER",
                /* 0x00BD >>> */ "MAP_0x00BD_CRASH",
                /* 0x00BE >>> */ "MAP_0x00BE_CRASH",
                /* 0x00BF >>> */ "MAP_0x00BF_CRASH",
                /* 0x00C0 >>> */ "MAP_0x00C0_CRASH",
                /* 0x00C1 >>> */ "MAP_0x00C1_CRASH",
                /* 0x00C2 >>> */ "MAP_0x00C2_CRASH",
                /* 0x00C3 >>> */ "MAP_0x00C3_CRASH",
                /* 0x00C4 */ "MAP_0C4_MT_JADE_SNAKE_GROVE",
                /* 0x00C5 */ "MAP_0C5_MT_TREASURE_CHAMBER",
                /* 0x00C6 */ "MAP_0C6_MT_KICKBALL_ARENA_1",
                /* 0x00C7 */ "MAP_0C7_GGM_MAIN_AREA",
                /* 0x00C8 */ "MAP_0C8_MT_KICKBALL_ARENA_2",
                /* 0x00C9 */ "MAP_0C9_MT_KICKBALL_ARENA_3",
                /* 0x00CA */ "MAP_0CA_GGM_FUEL_DEPOT",
                /* 0x00CB */ "MAP_0CB_GGM_CRUSHING_SHED",
                /* 0x00CC */ "MAP_0CC_GGM_FLOODED_CAVES",
                /* 0x00CD */ "MAP_0CD_GGM_WATER_STORAGE",
                /* 0x00CE */ "MAP_0CE_GGM_WATERFALL_CAVERN",
                /* 0x00CF */ "MAP_0CF_GGM_POWER_HUT_BASEMENT",
                /* 0x00D0 */ "MAP_0D0_GGM_CHUFFYS_CAB",
                /* 0x00D1 */ "MAP_0D1_GGM_BOSS_INSIDE_CHUFFYS_BOILER",
                /* 0x00D2 */ "MAP_0D2_GGM_GLOOMY_CAVERNS",
                /* 0x00D3 */ "MAP_0D3_GGM_GENERATOR_CAVERN",
                /* 0x00D4 */ "MAP_0D4_GGM_POWER_HUT",
                /* 0x00D5 */ "MAP_0D5_WW_WUMBAS_WIGWAM",
                /* 0x00D6 */ "MAP_0D6_WW_MAIN_AREA",
                /* 0x00D7 */ "MAP_0D7_GGM_TRAIN_STATION",
                /* 0x00D8 */ "MAP_0D8_GGM_PROSPECTORS_HUT",
                /* 0x00D9 */ "MAP_0D9_GGM_MUMBOS_SKULL",
                /* 0x00DA */ "MAP_0DA_GGM_TOXIC_GAS_CAVE",
                /* 0x00DB */ "MAP_0DB_GGM_CANARY_CAVE",
                /* 0x00DC */ "MAP_0DC_GGM_ORDNANCE_STORAGE",
                /* 0x00DD */ "MAP_0DD_WW_DODGEM_DOME_LOBBY",
                /* 0x00DE */ "MAP_0DE_WW_DODGEM_CHALLENGE_1V1",
                /* 0x00DF */ "MAP_0DF_WW_DODGEM_CHALLENGE_2V1",
                /* 0x00E0 */ "MAP_0E0_WW_DODGEM_CHALLENGE_3V1",
                /* 0x00E1 */ "MAP_0E1_WW_CRAZY_CASTLE_STOCKADE",
                /* 0x00E2 */ "MAP_0E2_WW_CRAZY_CASTLE_LOBBY",
                /* 0x00E3 */ "MAP_0E3_WW_CRAZY_CASTLE_PUMP_ROOM",
                /* 0x00E4 */ "MAP_0E4_WW_BALLOON_BURST_GAME",
                /* 0x00E5 */ "MAP_0E5_WW_HOOP_HURRY",
                /* 0x00E6 */ "MAP_0E6_WW_STAR_SPINNER",
                /* 0x00E7 */ "MAP_0E7_WW_THE_INFERNO",
                /* 0x00E8 >>> */ "MAP_0x00E8_CRASH",
                /* 0x00E9 */ "MAP_0E9_GGM_WUMBAS_WIGWAM",
                /* 0x00EA */ "MAP_0EA_WW_CAVE_OF_HORRORS",
                /* 0x00EB */ "MAP_0EB_WW_HAUNTED_CAVERN",
                /* 0x00EC */ "MAP_0EC_WW_TRAIN_STATION",
                /* 0x00ED */ "MAP_0ED_JRL_JOLLYS",
                /* 0x00EE */ "MAP_0EE_JRL_PAWNOS_EMPORIUM",
                /* 0x00EF */ "MAP_0EF_JRL_MUMBOS_SKULL",
                /* 0x00F0 >>> */ "MAP_0x00F0_CRASH",
                /* 0x00F1 */ "MAP_0F1_JRL_INSIDE_THE_UFO",
                /* 0x00F2 >>> */ "MAP_0x00F2_UNKNOWN",
                /* 0x00F3 >>> */ "MAP_0x00F3_CRASH",
                /* 0x00F4 */ "MAP_0F4_JRL_ANCIENT_SWIMMING_BATHS",
                /* 0x00F5 >>> */ "MAP_0x00F5_CRASH",
                /* 0x00F6 */ "MAP_0F6_JRL_ELECTRIC_EELS_LAIR",
                /* 0x00F7 */ "MAP_0F7_JRL_SEAWEED_SANCTUM",
                /* 0x00F8 */ "MAP_0F8_JRL_INSIDE_THE_BIG_FISH",
                /* 0x00F9 */ "MAP_0F9_WW_BOSS_MR_PATCH",
                /* 0x00FA */ "MAP_0FA_JRL_TEMPLE_OF_THE_FISHES",
                /* 0x00FB >>> */ "MAP_0x00FB_CRASH",
                /* 0x00FC */ "MAP_0FC_JRL_BOSS_LORD_WOO_FAK_FAK",
                /* 0x00FD >>> */ "MAP_0x00FD_CRASH",
                /* 0x00FE >>> */ "MAP_0x00FE_CRASH",
                /* 0x00FF */ "MAP_0FF_JRL_BLUBBERS_WAVE_RACE_HIRE",
                /* 0x0100 */ "MAP_100_GI_MAIN_AREA",
                /* 0x0101 */ "MAP_101_GI_FLOOR_1",
                /* 0x0102 */ "MAP_102_GI_TRAIN_STATION",
                /* 0x0103 */ "MAP_103_GI_WORKERS_QUARTERS",
                /* 0x0104 */ "MAP_104_GI_TRASH_COMPACTOR",
                /* 0x0105 */ "MAP_105_GI_ELEVATOR_SHAFT",
                /* 0x0106 */ "MAP_106_GI_FLOOR_2_MAIN",
                /* 0x0107 */ "MAP_107_GI_FLOOR_2_ELECTROMAGNET_CHAMBER",
                /* 0x0108 */ "MAP_108_GI_FLOOR_3_MAIN",
                /* 0x0109 */ "MAP_109_GI_FLOOR_3_BOILER_PLANT",
                /* 0x010A */ "MAP_10A_GI_FLOOR_3_PACKING_ROOM",
                /* 0x010B */ "MAP_10B_GI_FLOOR_4_MAIN",
                /* 0x010C */ "MAP_10C_GI_FLOOR_4_CABLE_ROOM",
                /* 0x010D */ "MAP_10D_GI_FLOOR_4_QUALITY_CONTROL",
                /* 0x010E */ "MAP_10E_GI_FLOOR_5",
                /* 0x010F */ "MAP_10F_GI_BASEMENT_AIR_CON_PLANT",
                /* 0x0110 */ "MAP_110_GI_BASEMENT_BOSS_REPAIR_DEPOT",
                /* 0x0111 */ "MAP_111_GI_BASEMENT_WASTE_DISPOSAL",
                /* 0x0112 */ "MAP_112_TDL_MAIN_AREA",
                /* 0x0113 */ "MAP_113_TDL_BOSS_TERRYS_NEST",
                /* 0x0114 */ "MAP_114_TDL_TRAIN_STATION",
                /* 0x0115 */ "MAP_115_TDL_OOGLE_BOOGLES_CAVE",
                /* 0x0116 */ "MAP_116_TDL_INSIDE_THE_MOUNTAIN",
                /* 0x0117 */ "MAP_117_TDL_RIVER_PASSAGE",
                /* 0x0118 */ "MAP_118_TDL_STYRACOSAURUS_FAMILY_CAVE",
                /* 0x0119 */ "MAP_119_TDL_UNGA_BUNGAS_CAVE",
                /* 0x011A */ "MAP_11A_TDL_STOMPING_PLAINS",
                /* 0x011B */ "MAP_11B_TDL_BONFIRE_CAVERN",
                /* 0x011C >>> */ "MAP_0x011C_CRASH",
                /* 0x011D >>> */ "MAP_0x011D_CRASH",
                /* 0x011E */ "MAP_11E_TDL_WUMBAS_WIGWAM_SMALL",
                /* 0x011F */ "MAP_11F_GI_WUMBAS_WIGWAM",
                /* 0x0120 */ "MAP_120_JRL_WUMBAS_WIGWAM",
                /* 0x0121 */ "MAP_121_GGM_INSIDE_CHUFFYS_WAGON",
                /* 0x0122 */ "MAP_122_TDL_WUMBAS_WIGWAM_BIG",
                /* 0x0123 */ "MAP_123_TDL_INSIDE_CHOMPAS_BELLY",
                /* 0x0124 */ "MAP_124_WW_SAUCER_OF_PERIL",
                /* 0x0125 */ "MAP_125_GI_WATER_SUPPLY_PIPE",
                /* 0x0126 */ "MAP_126_GGM_WATER_SUPPLY_PIPE",
                /* 0x0127 */ "MAP_127_HFP_LAVA_MAIN_AREA",
                /* 0x0128 */ "MAP_128_HFP_ICY_MAIN_AREA",
                /* 0x0129 */ "MAP_129_HFP_LAVA_TRAIN_STATION",
                /* 0x012A */ "MAP_12A_HFP_ICY_TRAIN_STATION",
                /* 0x012B */ "MAP_12B_HFP_LAVA_BOSS_CHILLI_BILLI",
                /* 0x012C */ "MAP_12C_HFP_ICY_BOSS_CHILLY_WILLY",
                /* 0x012D */ "MAP_12D_HFP_LAVA_KICKBALL_STADIUM_LOBBY",
                /* 0x012E */ "MAP_12E_HFP_LAVA_KICKBALL_STADIUM_1",
                /* 0x012F */ "MAP_12F_HFP_LAVA_KICKBALL_STADIUM_2",
                /* 0x0130 */ "MAP_130_HFP_LAVA_KICKBALL_STADIUM_3",
                /* 0x0131 */ "MAP_131_HFP_ICY_BOGGYS_IGLOO",
                /* 0x0132 */ "MAP_132_HFP_ICY_ICICLE_GROTTO",
                /* 0x0133 */ "MAP_133_HFP_LAVA_INSIDE_THE_VOLCANO",
                /* 0x0134 */ "MAP_134_HFP_LAVA_MUMBOS_SKULL",
                /* 0x0135 */ "MAP_135_HFP_ICY_WUMBAS_WIGWAM",
                /* 0x0136 */ "MAP_136_CCL_MAIN_AREA",
                /* 0x0137 */ "MAP_137_CCL_INSIDE_THE_TRASH_CAN",
                /* 0x0138 */ "MAP_138_CCL_INSIDE_THE_CHEESE_WEDGE",
                /* 0x0139 */ "MAP_139_CCL_ZUBBAS_NEST",
                /* 0x013A */ "MAP_13A_CCL_CENTRAL_CAVERN",
                /* 0x013B */ "MAP_13B_WW_CRAZY_CASTLE_STOCKADE_SAUCER",
                /* 0x013C */ "MAP_13C_WW_STAR_SPINNER_SAUCER",
                /* 0x013D */ "MAP_13D_CCL_INSIDE_THE_POT_O_GOLD",
                /* 0x013E */ "MAP_13E_CCL_MUMBOS_SKULL",
                /* 0x013F */ "MAP_13F_CCL_BOSS_MINGY_JONGOS_SKULL",
                /* 0x0140 */ "MAP_140_CCL_WUMBAS_WIGWAM",
                /* 0x0141 */ "MAP_141_SM_BOSS_INSIDE_THE_DIGGER_TUNNEL",
                /* 0x0142 */ "MAP_142_JV_MAIN_AREA",
                /* 0x0143 */ "MAP_143_JV_BOTTLES_HOUSE",
                /* 0x0144 */ "MAP_144_JV_KING_JINGALINGS_THRONE_ROOM",
                /* 0x0145 */ "MAP_145_JV_GREEN_JINJO_HOUSE",
                /* 0x0146 */ "MAP_146_JV_BLACK_JINJO_HOUSE",
                /* 0x0147 */ "MAP_147_JV_YELLOW_JINJO_HOUSE",
                /* 0x0148 */ "MAP_148_JV_BLUE_JINJO_HOUSE",
                /* 0x0149 >>> */ "MAP_149_JV_UNUSED_JINJO_HOUSE",
                /* 0x014A */ "MAP_14A_JV_BROWN_JINJO_HOUSE",
                /* 0x014B */ "MAP_14B_JV_ORANGE_JINJO_HOUSE",
                /* 0x014C */ "MAP_14C_JV_PURPLE_JINJO_HOUSE",
                /* 0x014D */ "MAP_14D_JV_RED_JINJO_HOUSE",
                /* 0x014E */ "MAP_14E_JV_WHITE_JINJO_HOUSE",
                /* 0x014F */ "MAP_14F_IOH_WOODED_HOLLOW",
                /* 0x0150 */ "MAP_150_IOH_HEGGYS_EGG_SHED",
                /* 0x0151 */ "MAP_151_IOH_JIGGYWIGGYS_TEMPLE",
                /* 0x0152 */ "MAP_152_IOH_PLATEAU",
                /* 0x0153 */ "MAP_153_IOH_HONEY_BS_HIVE",
                /* 0x0154 */ "MAP_154_IOH_PINE_GROVE",
                /* 0x0155 */ "MAP_155_IOH_CLIFF_TOP",
                /* 0x0156 */ "MAP_156_IOH_MUMBOS_SKULL",
                /* 0x0157 */ "MAP_157_IOH_WUMBAS_WIGWAM",
                /* 0x0158 */ "MAP_158_FILE_SELECT_SCREEN",
                /* 0x0159 */ "MAP_159_CUTSCENE_OPENING_CUTSCENE",
                /* 0x015A */ "MAP_15A_IOH_WASTELAND",
                /* 0x015B */ "MAP_15B_IOH_BOSS_INSIDE_ANOTHER_DIGGER_TUNNEL",
                /* 0x015C */ "MAP_15C_IOH_QUAGMIRE",
                /* 0x015D */ "MAP_15D_CK_MAIN_AREA",
                /* 0x015E */ "MAP_15E_CK_BOSS_THE_GATEHOUSE",
                /* 0x015F */ "MAP_15F_CK_TOWER_OF_TRAGEDY",
                /* 0x0160 */ "MAP_160_CK_GUN_CHAMBER",
                /* 0x0161 */ "MAP_161_CCL_CANARY_MARY_RACE",
                /* 0x0162 */ "MAP_162_GI_FLOOR_4_CLINKERS_CAVERN",
                /* 0x0163 */ "MAP_163_GGM_ORDNANCE_STORAGE_ENTRANCE",
                /* 0x0164 */ "MAP_164_MULTIPLAYER_GI_CLINKERS_CAVERN",
                /* 0x0165 */ "MAP_165_MULTIPLAYER_GGM_ORDNANCE_STORAGE",
                /* 0x0166 */ "MAP_166_MULTIPLAYER_MT_TARGITZANS_TEMPLE",
                /* 0x0167 */ "MAP_167_PARADE_MT",
                /* 0x0168 */ "MAP_168_PARADE_HFP_ICY",
                /* 0x0169 */ "MAP_169_PARADE_JV_BOTTLES_HOUSE",
                /* 0x016A */ "MAP_16A_PARADE_CK_GUN_CHAMBER",
                /* 0x016B >>> */ "MAP_0x016B_CRASH",
                /* 0x016C >>> */ "MAP_0x016C_CRASH",
                /* 0x016D >>> */ "MAP_0x016D_CRASH",
                /* 0x016E >>> */ "MAP_0x016E_CRASH",
                /* 0x016F */ "MAP_16F_GGM_CANARY_MARY_RACE_1",
                /* 0x0170 */ "MAP_170_GGM_CANARY_MARY_RACE_2",
                /* 0x0171 */ "MAP_171_TDL_MUMBOS_SKULL",
                /* 0x0172 */ "MAP_172_GI_MUMBOS_SKULL",
                /* 0x0173 */ "MAP_173_SM_BANJOS_HOUSE",
                /* 0x0174 >>> */ "MAP_0x0174_CRASH",
                /* 0x0175 >>> */ "MAP_0x0175_CRASH",
                /* 0x0176 */ "MAP_176_WW_MUMBOS_SKULL",
                /* 0x0177 */ "MAP_177_MT_TARGITZANS_SLIGHTLY_SACRED_CHAMBER",
                /* 0x0178 */ "MAP_178_MT_TARGITZANS_TEMPLE",
                /* 0x0179 */ "MAP_179_MT_TARGITZANS_TEMPLE_LOBBY",
                /* 0x017A */ "MAP_17A_MT_BOSS_TARGITZANS_REALLY_SACRED_CHAMBER",
                /* 0x017B */ "MAP_17B_MULTIPLAYER_WW_BALLOON_BURST",
                /* 0x017C */ "MAP_17C_MULTIPLAYER_WW_JUMP_THE_HOOPS",
                /* 0x017D */ "MAP_17D_GI_PACKING_GAME",
                /* 0x017E */ "MAP_17E_CUTSCENE_ZOMBIFIED_THRONE_ROOM",
                /* 0x017F */ "MAP_17F_MT_KICKBALL_ARENA_4",
                /* 0x0180 */ "MAP_180_HFP_LAVA_KICKBALL_ARENA",
                /* 0x0181 */ "MAP_181_JRL_SEA_BOTTOM_CAVERN",
                /* 0x0182 */ "MAP_182_MULTIPLAYER_JRL_SUBMARINE",
                /* 0x0183 */ "MAP_183_MULTIPLAYER_TDL_CHOMPAS_BELLY",
                /* 0x0184 >>> */ "MAP_0x0184_CRASH_UNUSED_PIPE",
                /* 0x0185 */ "MAP_185_CCL_TRASH_CAN_MINI",
                /* 0x0186 */ "MAP_186_WW_DODGEMS",
                /* 0x0187 */ "MAP_187_GI_SEWER_ENTRANCE",
                /* 0x0188 */ "MAP_188_MULTIPLAYER_CCL_ZUBBAS_NEST",
                /* 0x0189 */ "MAP_189_MULTIPLAYER_CK_TOWER_OF_TRAGEDY",
                /* 0x018A */ "MAP_18A_CK_INSIDE_HAG_1",
                /* 0x018B */ "MAP_18B_INTRO_SCREEN",
                /* 0x018C */ "MAP_18C_CUTSCENE_INTRO_TO_BOB",
                /* 0x018D */ "MAP_18D_CUTSCENE_JINGALING_ZAPPED",
                /* 0x018E */ "MAP_18E_CUTSCENE_MEANWHILE_JINGALING_ZAPPING",
                /* 0x018F */ "MAP_18F_CUTSCENE_BOB_PREPARING_TO_FIRE",
                /* 0x0190 */ "MAP_190_CUTSCENE_JINGALING_GETTING_ZAPPED",
                /* 0x0191 */ "MAP_191_CUTSCENE_SAD_PARTY_AT_BOTTLES",
                /* 0x0192 */ "MAP_192_CUTSCENE_BOTTLES_EATING_BURNT_FOOD",
                /* 0x0193 */ "MAP_193_CUTSCENE_BOTTLES_ENERGY_RESTORING",
                /* 0x0194 */ "MAP_194_CUTSCENE_BK_RUNNING_INTO_GUN_CHAMBER",
                /* 0x0195 */ "MAP_195_CUTSCENE_BK_AT_BOBS_CONTROLS",
                /* 0x0196 */ "MAP_196_CUTSCENE_KICK_ABOUT",
                /* 0x0197 */ "MAP_197_CUTSCENE_I_WONDER_WHAT_WE_WILL_HIT",
                /* 0x0198 */ "MAP_198_CUTSCENE_JINGALING_RESTORING",
                /* 0x0199 */ "MAP_199_CUTSCENE_ALL_JINJOS_HAPPY_AGAIN",
                /* 0x019A */ "MAP_19A_CK_BOSS_HAG_1",
                /* 0x019B */ "MAP_19B_JV_JINGALINGS_ZOMBIFIED_THRONE_ROOM",
                /* 0x019C */ "MAP_19C_CUTSCENE_ROLL_THE_CREDITS",
                /* 0x019D */ "MAP_19D_CUTSCENE_PARADE",
                /* 0x019E >>> */ "MAP_0x019E_CRASH",
                /* 0x019F >>> */ "MAP_0x019F_CRASH",
                /* 0x01A0 >>> */ "MAP_0x01A0_UNKNOWN",
                /* 0x01A1 >>> */ "MAP_0x01A1_UNKNOWN",
                /* 0x01A2 >>> */ "MAP_0x01A2_UNKNOWN",
                /* 0x01A3 >>> */ "MAP_0x01A3_UNKNOWN",
                /* 0x01A4 >>> */ "MAP_0x01A4_UNKNOWN",
                /* 0x01A5 >>> */ "MAP_0x01A5_UNKNOWN",
                /* 0x01A6 */ "MAP_1A6_JRL_SMUGGLERS_CAVERN",
                /* 0x01A7 */ "MAP_1A7_JRL_MAIN_AREA",
                /* 0x01A8 */ "MAP_1A8_JRL_ATLANTIS",
                /* 0x01A9 */ "MAP_1A9_JRL_SEA_BOTTOM",

                "MAP_1AA_MAX" // 0x1AA
            ];

            let idx = val - 0xA0;

            if (idx < 0 || idx > MAP.length)
                // FATAL(`Value not a valid MAP: ${val}`);
                return "0x" + val.toString(16).toUpperCase();

            return MAP[idx];
        }
        case "MUSIC":
        {
            let MUSIC =
            [
                "MUSIC_00_SELECT_MENU_OPTION_1",
                "MUSIC_01_GET_NOTE_NEST",
                "MUSIC_02_GET_JINJO",
                "MUSIC_03_GET_RED_FEATHER",
                "MUSIC_04_GET_EGG",
                "MUSIC_05_GET_JIGGY",
                "MUSIC_06_GET_GOLD_FEATHER",
                "MUSIC_07_GET_EXTRA_LIFE",
                "MUSIC_08_GET_HONEY",
                "MUSIC_09_GET_EMPTY_HONEYCOMB",
                "MUSIC_0A_GET_HEALTH_EXTENSION",
                "MUSIC_0B_DEATH",
                "MUSIC_0C_TRANSFORMATION",
                "MUSIC_0D_WONDERWING",
                "MUSIC_0E_PUZZLE_CORRECT",
                "MUSIC_0F_PUZZLE_WRONG",
                "MUSIC_10_PUZZLE_COMPLETE",
                "MUSIC_11_RESCUE_JINJO_GROUP",
                "MUSIC_12_GAME_OVER",
                "MUSIC_13_UNK",
                "MUSIC_14_GET_TREBLE_CLEF",
                "MUSIC_15_UNK",
                "MUSIC_16_MINIGAME_WIN",
                "MUSIC_17_MINIGAME_LOSE",
                "MUSIC_18_JIGGY_SPAWN",
                "MUSIC_19_WRONG",
                "MUSIC_1A_MUMBOS_SKULL",
                "MUSIC_1B_GET_ALL_JIGGIES",
                "MUSIC_1C_SPARKLES",
                "MUSIC_1D_WHISTLE_OUT",
                "MUSIC_1E_WHISTLE_IN",
                "MUSIC_1F_TURBO_TRAINERS",
                "MUSIC_20_WADING_BOOTS",
                "MUSIC_21_UNK",
                "MUSIC_22_UNK",
                "MUSIC_23_UNK",
                "MUSIC_24_PAUSE_MENU",
                "MUSIC_25_UNK",
                "MUSIC_26_UNK",
                "MUSIC_27_UNK",
                "MUSIC_28_UNK",
                "MUSIC_29_UNK",
                "MUSIC_2A_UNK",
                "MUSIC_2B_TURBO_TRAINERS_QUICK",
                "MUSIC_2C_UNK",
                "MUSIC_2D_UNK",
                "MUSIC_2E_PUZZLE_START",
                "MUSIC_2F_PUZZLE_PLACE_PIECE",
                "MUSIC_30_PUZZLE_REMOVE_PIECE",
                "MUSIC_31_PUZZLE_START_2",
                "MUSIC_32_SM_MAIN",
                "MUSIC_33_BANJOS_HOUSE",
                "MUSIC_34_GL_ENTRANCE",
                "MUSIC_35_UNK",
                "MUSIC_36_UNK",
                "MUSIC_37_WUMBAS_WIGWAM",
                "MUSIC_38_TARGITZAN_1",
                "MUSIC_39_MT_MAIN",
                "MUSIC_3A_JAMJARS",
                "MUSIC_3B_TARGITZAN_2",
                "MUSIC_3C_UNK",
                "MUSIC_3D_MINIGAME",
                "MUSIC_3E_GGM_MAIN",
                "MUSIC_3F_GI_MAIN",
                "MUSIC_40_WW_MAIN",
                "MUSIC_41_HFP_MAIN",
                "MUSIC_42_GGM_MINIGAME",
                "MUSIC_43_MT_KICKBALL_DONE",
                "MUSIC_44_CHEATO",
                "MUSIC_45_JRL_MAIN",
                "MUSIC_46_UNK",
                "MUSIC_47_UNK",
                "MUSIC_48_GGM_BOSS",
                "MUSIC_49_FUN_N_GAMES",
                "MUSIC_4A_checkme",
                "MUSIC_4B_JRL_ATLANTIS",
                "MUSIC_4C_WW_BOSS",
                "MUSIC_4D_HFP_BOGGYS_HOUSE",
                "MUSIC_4E_TDL_BOSS",
                "MUSIC_4F_JRL_ALIENS",
                "MUSIC_50_JRL_ALIENS_SAVED",
                "MUSIC_51_UNK",
                "MUSIC_52_TDL_MAIN",
                "MUSIC_53_JRL_CHRIS_P_BACON",
                "MUSIC_54_TDL_CHOMPASAURUS",
                "MUSIC_55_KLUNGO",
                "MUSIC_56_HFP_BOSS",
                "MUSIC_57_CCL_MAIN",
                "MUSIC_58_IOH_MAIN",
                "MUSIC_59_IOH_JV",
                "MUSIC_5A_IOH_JV_SAD_JINJOS",
                "MUSIC_5B_IOH_JV_HAPPY_JINJOS",
                "MUSIC_5C_IOH_JV_THRONE",
                "MUSIC_5D_IOH_JV_THRONE_ZOMBIE",
                "MUSIC_5E_IOH_JIGGYWIGGY",
                "MUSIC_5F_IOH_HONEY_B",
                "MUSIC_60_MUMBO_SPELL",
                "MUSIC_61_JRL_BOSS",
                "MUSIC_62_IOH_JV_BOTTLES_HOUSE",
                "MUSIC_63_GI_BOSS",
                "MUSIC_64_CLOCKWORK_KAZ",
                "MUSIC_65_SPRINGY_STEP",
                "MUSIC_66_CLAW_CLAMBER",
                "MUSIC_67_FILE_SELECT",
                "MUSIC_68_CLOCKWORK_KAZ_SHORT",
                "MUSIC_69_GET_EGG_CLOCKWORK",
                "MUSIC_6A_GET_EGG_FIRE",
                "MUSIC_6B_GET_EGG_ICE",
                "MUSIC_6C_GET_EGG_GRENADE",
                "MUSIC_6D_SELECT_EGG_CLOCKWORK",
                "MUSIC_6E_SELECT_EGG_FIRE",
                "MUSIC_6F_SELECT_EGG_ICE",
                "MUSIC_70_SELECT_EGG_GRENADE",
                "MUSIC_71_SELECT_EGG_BLUE",
                "MUSIC_72_GET_CHEATO_PAGE",
                "MUSIC_73_GET_WW_TICKET",
                "MUSIC_74_DAMAGED",
                "MUSIC_75_CK_MAIN",
                "MUSIC_76_CCL_CANARY_RACE",
                "MUSIC_77_CHEATO_PAGE_SPAWN",
                "MUSIC_78_GET_EGG_PROXIMITY",
                "MUSIC_79_SELECT_EGG_PROXIMITY",
                "MUSIC_7A_CK_BOSS",
                "MUSIC_7B_CS_INTRO",
                "MUSIC_7C_CS_GRUNTY_DEFEATED",
                "MUSIC_7D_CS_MAIN_INTRO",
                "MUSIC_7E_CK_TOT",
                "MUSIC_7F_IOH_HEGGY",
                "MUSIC_80_MISC_HONEY_1",
                "MUSIC_81_MISC_HONEY_2",
                "MUSIC_82_CS_CREDITS",
                "MUSIC_83_JINGALING_PUZZLE_checkme",
                "MUSIC_84_MT_KICKBALL_START",
                "MUSIC_85_GGM_ALTERNATE",
                "MUSIC_86_GI_CLINKERS",
                "MUSIC_87_CS_MEANWHILE",
                "MUSIC_88_CS_HOW_DO_I_GET_MY_BODY_BACK",
                "MUSIC_89_CS_ABOUT_TO_SHOOT_BOB",
                "MUSIC_8A_CS_DRAINING_JINGALING",
                "MUSIC_8B_CS_HES_JUST_A_ZOMBIE",
                "MUSIC_8C_CS_LETS_SHOOT",
                "MUSIC_8D_WIND",
                "MUSIC_8E_CS_WE_NEED_TO_SAVE",
                "MUSIC_8F_CS_WHO_KNOWS_WHAT_WE_WILL_HIT",
                "MUSIC_90_CS_YOU_OWE_ME_AN_APOLOGY",
                "MUSIC_91_CS_IM_SAVED_THANKS",
                "MUSIC_92_TICK_TICK_TICK",
                "MUSIC_93_CS_BOTTLES_NEXT",
                "MUSIC_94_BOTTLES_REVIVAL",
                "MUSIC_95_IOH_JV_BOTTLES_HAPPY_PARTY",
                "MUSIC_96_SelectingCheat",
                "MUSIC_97_DeselectingCheat",
                "MUSIC_98_IOH_JV_BOTTLES_SAD_PARTY",
                "MUSIC_99_CS_KICK_AROUND",
                "MUSIC_9A_IOH_JV_BOTTLES_RAVE",
                "MUSIC_9B_CLOCK_TICK_checkme",
                "MUSIC_9C_JINJONATOR_HIT_1",
                "MUSIC_9D_JINJONATOR_HIT_2",
                "MUSIC_9E_JINJONATOR_HIT_3",
                "MUSIC_9F_JINJONATOR_HIT_4",
                "MUSIC_A0_JINJONATOR_HIT_5",
                "MUSIC_A1_CRASH",
                "MUSIC_A2_UNK",
            ];

            return MUSIC[val];
        }
        default: break;
    }

    //# Unhandled type, treat generically

    switch (base)
    {
        case 16:
            return "0x" + val.toString(16).toUpperCase().padStart(prepadwidth, "0");
        case 2:
            return "0b" + val.toString(2).padStart(prepadwidth, "0");
        default:
            return val.toString().padStart(prepadwidth, " ");
    }
}

/**
 * Declare a member of a struct
 * @param {string} type  mnemonic for type. e.g. u16, MAP, u32, s8, etc. affects the output format
 * @param {string} name  name of the struct member
 * 
 * @param {number} width width of the member in bits. can be inferred by type if not specified.
 * @param {number} base  the base to output the value as when stringifying
 * 
 * @returns 
 */
function _member(type, name, { width=undefined, base=16, prepadwidth=0 }={})
{
    if (width === undefined)
    {
        switch (type.toLowerCase())
        {
            case "s8":   width = 8;  break;
            case "u8":   width = 8;  break;
            case "s16":  width = 16; break;
            case "u16":  width = 16; break;
            case "s32":  width = 32; break;
            case "u32":  width = 32; break;
            case "s64":  width = 64; break;
            case "u64":  width = 64; break;
            case "int":  width = 32; break;
            case "long": width = 32; break;
            case "f32":  width = 32; break;
            case "f64":  width = 64; break;
            case "WORD": width = 32; break;
            case "HALF": width = 16; break;
            case "BYTE": width = 8;  break;

            case "vec2f": width = 32 * 2; break;
            case "vec3f": width = 32 * 3; break;

            default:
            {
                FATAL(`Could not autodetect width for member: ${type} ${name}`);
            }
        }
    }

    return { name, type, width, base, prepadwidth };
}

/**
 * Allow declaring a member with natural C syntax
 * 
 * Also allows specifying the stringify base as e.g.: "@16" or "@ 16"
 *   Can prepad base with zeros like so: "@16-4" which would give values like 0x0003, 0x0004, etc.
 *     Note: with base 10, prepads with spaces not zeroes
 * 
 * @param {string} declaration e.g. "MAP map : 16" or "int height", can end in semicolon
 */
function member(declaration)
{
    //# Remove semicolons
    declaration = declaration.replace(/;+$/, "");

    //- Process base
    let base = 16;
    let prepadwidth = 0;
    {
        let m;

        m = declaration.match(/@\s*(\d+)-(\d+)/);
        if (m)
        {
            //# Includes base and prepad width
            base        = parseInt(m[1]);
            prepadwidth = parseInt(m[2]);
        }
        else
        {
            m = declaration.match(/@\s*(\d+)/);
            if (m)
            {
                //# Includes base
                base = parseInt(m[1]);
            }
        }

        //# Remove base
        declaration = declaration.replace(/\s*@.*$/g, "").trim();
    }

    //- Process width in bits
    let width = undefined;
    {
        let m = declaration.match(/:\s*(\d+)/);
        if (m)
            //# Includes width
            width = parseInt(m[1]);

        //# Remove width
        declaration = declaration.replace(/\s*:.*$/g, "").trim();
    }

    //- Extract name token
    //# Do this first, since type can be multiple words long
    let name = declaration.replace(/^.+ /g, "").trim();
    
    //- Extract type
    //# Do this last, since type can be multiple words long
    let type = declaration.replace(/ .+$/g, "").trim();

    return _member(type, name, { width, base, prepadwidth });
}

/**
 * Parse a byte string and then incrementally return bits as requested.
 * @param {string} bytes e.g. "00 d6 00 01 01 a7 " ...
 */
function bitwrapper(bytes)
{
    let _arr = bytes.trim().split(/\s+/g).map(e => parseInt(e, 16));

    return {
        //# current offset (in bits)
        _curr: 0,
        //# array of bytes
        _arr,
        //# total size in bits
        _size: _arr.length * 8,

        /**
         * Return a value from the array from offset
         * @param {number} offset 
         * @param {number} width 
         * @returns 
         */
        _extract(offset, width)
        {
            let out = 0;

            for (let remaining = width; remaining > 0; remaining--)
            {
                let byte = offset >> 3;
                let bit  = offset & 7;

                let val = this._arr[byte];

                out |=  (val >>> (7 - bit)) & 1;
                out <<= 1;

                offset++;
            }

            return out >>> 1;
        },

        /**
         * Return a value from the current position, and increment the offset
         * @param {number} width 
         * @returns 
         */
        pull(width)
        {
            let out = this._extract(this._curr, width);

            this._curr += width;

            return out;
        },

        get remainingBitsInArr()
        {
            return this._size - this._curr;
        },

        /**
         * Stringify the current array into a C array, based on a struct definition
         * @param {string} members lines of member declarations that makes up an element of the array
         * 
         * e.g. "u16 unk @10-0"
         *      "TYPE NAME : WIDTH_IN_BITS @ BASE - ZERO_PREPAD"
         * 
         * e.g. codify(`MAP map : 16; \n u16 unk @10; u32 ptr @16-8`);
         */
        codify(members)
        {
            //# Convert each line into a member()
            let memberArr = members.trim().split(/(?:\r?\n)/g).map(e => e.trim());

            let structdef = memberArr.map(member);

            //# total size of struct in bits
            let structSize = structdef.reduce((a, e) => a + e.width, 0);

            let out = [];

            while (this.remainingBitsInArr >= structSize)
            {
                let e = [];

                for (let member of structdef)
                {
                    let val = this.pull(member.width);

                    let valstr = dehardcode_val(val,
                        {
                            type:        member.type,
                            base:        member.base,
                            prepadwidth: member.prepadwidth,
                        }
                    );

                    e.push(valstr);
                }

                out.push(e);
            }

            //- Calculate padding for each member
            let padding = (new Array(memberArr.length)).fill(0);
            {
                for (let i = 0; i < padding.length; i++)
                {
                    for (let e of out)
                    {
                        //# Take into account the ", " delimiter that we'll add later
                        let delimiterPad = i < padding.length - 1 ? 2 : 0;

                        padding[i] = Math.max(padding[i], e[i].length + delimiterPad);
                    }
                }
            }

            //- Generate element string
            let lines = [];
            {
                for (let e of out)
                {
                    let line = [];

                    for (let [idx, str] of e.entries())
                    {
                        let paddedstr = str;

                        if (idx < e.length - 1)
                            paddedstr += ", ";

                        paddedstr = paddedstr.padEnd(padding[idx], " ");

                        line.push(paddedstr);
                    }

                    lines.push(line.join(""));
                }
            }

            //- Stringify all
            {
                //# Calculate the index of the current line, autopadded to the right width
                const p = i => i.toString().padStart(~~Math.log10(out.length) + 1, " ");

                return lines.map((line, i) => `/* ${p(i)} */ { ${line} },`).join("\n");
            }
        },
    };
}

async function main()
{

    let bytes = "00 d6 00 01 01 a7 00 11 01 a6 00 16 01 a8 00 12 01 a9 00 13 00 f4 00 05 00 f6 00 05 00 f7 00 05 00 fa 00 05 00 fc 00 05 00 f8 00 06 00 e7 00 07 00 f1 00 08 01 26 00 0b 01 25 00 0a 01 81 00 09 01 82 00 09 00 bb 00 0d 00 b8 00 0e 00 c6 00 0c 00 c8 00 0c 00 c9 00 0c 01 2e 00 0c 01 2f 00 0c 01 30 00 0c 01 27 00 14 01 80 00 0c 01 2d 00 17 01 5d 00 15 01 42 00 0f 01 55 00 10 ff ff 00 00";

    console.log(

        // e.g. "u16 unk @10-0"
        //      "TYPE NAME : WIDTH_IN_BITS @ BASE - ZERO_PREPAD"
        bitwrapper(bytes).codify(`
            MAP map : 16;
            u16 unk @10;
        `
    ));

    // member("MAP", "map", { width: 16 }),
    // member("u16", "unk"),

}

main();




