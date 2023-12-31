#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "include/2.0L/PR/ultratypes.h"

#include "include/struct/object.h"
#include "include/struct/player.h"

#include "include/enum/flag.h"
#include "include/enum/item.h"
#include "include/enum/map.h"
#include "include/enum/music.h"

void func_800C3FC0(u32, f32, u32);
void func_800C9BB4(f32, u32, f32, u32);


u32   func_800B2840(void);
u32   func_800B2344(u32);
void *func_800B27A0(void *);

/*<0x80019E98, 0x80019998, 0x800199C8, 0x800199C8>*/ void fn_memset(void *, u32, u32);
/*<0x8001BBA0, 0x8001B560, 0x8001B590, 0x8001B590>*/ void fn_memcpy(void *, void *, u32);
void  fn_memcpy_fast(void *, void *, u32);

void func_8009BC08       (Bo *, Vec3f *);
void fn_player_vel_cpy   (Bo *, Vec3f *);
f32  fn_gamespeed_get    (void);
void fn_vec_scale        (Vec3f *, f32);
void fn_vec_add_direct   (Vec3f *, Vec3f *);
void func_8009B98C       (Bo *, Vec3f *);


/* ref from -> fxkern */
s32  fn_font_char_visual_width_get(s32, u8);
void fn_currFont_set(s32);
void fn_currFont_reset_params(void);
void fn_currFont_size_set(f32);
void fn_gfx_head_printing(Gfx **);
void fn_gfx_tail_printing(Gfx **);
void fn_gfx_print_char(Gfx **, s32, s32, u8);


/* flag */
bool fn_flag_get(FLAG flag);
void fn_flag_set(FLAG flag, bool value);
void fn_flag_set_FALSE(FLAG flag);
void fn_flag_set_TRUE(FLAG flag);
s32  fn_flag_get_multi(FLAG flag, u32 width);
void fn_flag_set_multi(FLAG flag, s32 value, u32 width);
s32  fn_flag_get_and_increment_multi(FLAG flag, u32 width);
s32  fn_flag_get_multi_sum(FLAG flag, u32 width);
bool fn_flag_get_and_set(FLAG flag, bool value);

bool fn_ability_has(s32 abilityIdx);
void func_800D517C(void);

void fn_flag_set_675_TRUE(void);

MAP gsWorldGetSection(void);

s32 fn_rom_fetch_WORD(u32 addr, u32 *dst);

s32 fn_SPITEM_count_get(u32);

/* gcwater */
void *func_800BEB28(s32);
void *func_800B2720(void *);
s32   func_800AAD80(void *);

void func_80015778(void);

bool func_800D3948(void);


void *fn_malloc_temp(u32 size);
/**
 * [type]
 *   0 : temporary
 *   1 : permanent
 *   2 : unk
 */
void *fn_malloc     (u32 size, u32 type);
void  fn_free       (void *ptr);

/*<0x000050F0, 0x000050B0, 0x000050B0, 0x000050B0>*/ void __BUILD_INFO_AREA(void); //! not a function

/*<0x8001D96C, 0x8001D06C, 0x8001D09C, 0x8001D09C>*/ void fn_8001D96C(void);
/*<0x8001D9CC, 0x8001D0CC, 0x8001D0FC, 0x8001D0FC>*/ void fn_8001D9CC(u32, u32);
/*<0x8002DC20, 0x8002D1C0, 0x8002D1A0, 0x8002D1A0>*/ void fn_8002DC20(char *, char *, ...);
/*<0x8001B3C0, 0x8001ADB0, 0x8001ADE0, 0x8001ADE0>*/ u32  HEAP_get_occupied_size(void);

/*<0x80014ED4, 0x80014EE4, 0x80014E44, 0x80014E44>*/ Framebuffer *FRAMEBUFFER_get_computing(void);
/*<0x80014F00, 0x80014F10, 0x80014E70, 0x80014E70>*/ Framebuffer *FRAMEBUFFER_get_active(void);
/*<0x8001DB90, 0x8001D288, 0x8001D2B8, 0x8001D2B8>*/ void FRAMEBUFFER_8001DB90(Framebuffer *, s32, s32, void *);
/*<0x80015430, 0x80015440, 0x80015364, 0x80015364>*/ void FRAMEBUFFER_swap_to(u32);
/*<0x80014F38, 0x80014F48, 0x80014EA8, 0x80014EA8>*/ u32  FRAMEBUFFER_get_computing_idx(void);
/*<0x8001DA60, 0x8001D158, 0x8001D188, 0x8001D188>*/ void FRAMEBUFFER_8001DA60(Framebuffer *);
/*<0x80014EC8, 0x80014ED8, 0x80014E38, 0x80014E38>*/ u32  FRAMEBUFFER_get_size(void);

/*<0x8001D3D8, 0x8001CAD8, 0x8001CB08, 0x8001CB08>*/ void DEBUGGER_printf_at_pos(s32 x, s32 y, char *f, ...);
/*<0x8001D37C, 0x8001CA7C, 0x8001CAAC, 0x8001CAAC>*/ void DEBUGGER_printf(char *f, ...);
/*<0x8001E7A0, 0x8001DE20, 0x8001DE50, 0x8001DE50>*/ u32  DEBUGGER_fn_8001E7A0(u32);
/*<0x800F21C4, 0x800ED80C, 0x800F85DC, 0x800F847C>*/ u32  DEBUGGER_get_float_error_type(f32);

/*<0x8001DDA4, 0x8001D474, 0x8001D4A4, 0x8001D4A4>*/ OSThread *THREAD_get_by_idx(s32 threadIdx);
/*<0x8001D98C, 0x8001D08C, 0x8001D0BC, 0x8001D0BC>*/ void fn_8001D98C(u32);

/*<0x800DABF0, 0x800D7E68, 0x800E2C38, 0x800E2AD8>*/ void SAVEDATA_get_FB4_size_and_addr(s32 *dstSize, void **dstAddr);
/*<0x800D21B0, 0x800CF930, 0x800DA6A0, 0x800DA580>*/ void SAVEDATA_get_minigame_scores_size_and_addr(s32 *dstSize, void **dstAddr);

/*<0x800D2054, 0x800CF7D4, 0x800DA544, 0x800DA424>*/ void minigame_highscore_set(u32, u32, u32);
/*<0x800D3E14, 0x800D1554, 0x800DC2F4, 0x800DC1C4>*/ u32  CHEAT_available_get(u32);
/*<0x800FC6B0, 0x800F7170, 0x80101FA0, 0x80101DE0>*/ void MUSIC_play_sfx_2_bgm(MUSIC);
/*<0x800FE890, 0x800F932C, 0x8010415C, 0x80103F9C>*/ s32  gMusicObj_playThroughLz_get(void);
/*<0x800FE844, 0x800F92E0, 0x80104110, 0x80103F50>*/ void gMusicObj_playThroughLz_set(u32);
/*<0x800FE734, 0x800F91D0, 0x80104000, 0x80103E40>*/ void gMusicObj_0x17_set(u32);
/*<0x800FCCD4, 0x800F7794, 0x801025C4, 0x80102404>*/ bool MUSIC_track_is_currently_playing(s32);
/*<0x800FE89C, 0x800F9338, 0x80104168, 0x80103FA8>*/ void gMusicObj_0x0F_set_to_1(void);
/*<0x800FC884, 0x800F7344, 0x80102174, 0x80101FB4>*/ void MUSIC_800FB774(void);
/*<0x800FC348, 0x800F6E08, 0x80101C38, 0x80101A78>*/ void MUSIC_800FC348(s32, s32, s32);
/*<0x800FECB8, 0x800F9760, 0x80104590, 0x801043D0>*/ void MUSIC_800FECB8(s32);
/*<0x800FEC60, 0x800F96FC, 0x8010452C, 0x8010436C>*/ void MUSIC_800FEC60(s32);
/*<0x800FDC28, 0x800F8700, 0x80103530, 0x80103370>*/ void MUSIC_800FDC28(s32);
/*<0x800FC2C4, 0x800F6D84, 0x80101BB4, 0x801019F4>*/ void MUSIC_800FC2C4(s32, s32);
/*<0x800FE3EC, 0x800F8EC4, 0x80103CF4, 0x80103B34>*/ void MUSIC_800FE3EC(void);
/*<0x800FC74C, 0x800F720C, 0x8010203C, 0x80101E7C>*/ void MUSIC_800FC74C(s32);
/*<0x80016DF8, 0x80016CB8, 0x80016CE8, 0x80016CE8>*/ void MUSIC_80016DF8(s32);
/*<0x800FEDC4, 0x800F9884, 0x801046B4, 0x801044F4>*/ void fn_800FEDC4(s32, s32, f32, f32);
/*<0x800F3320, 0x800EE670, 0x800F94A0, 0x800F92E0>*/ void fn_800F3320(char *, void *, void *, f32);
/*<0x800F2EA0, 0x800EE260, 0x800F9090, 0x800F8ED0>*/ void fn_800F2EA0(s32, char *);

/*<0x800157E0, 0x800157F0, 0x80015810, 0x80015810>*/ void WIDESCREEN_set(bool enabled);
#if TVTYPE_NTSC
void SCREEN_DIMENSIONS_set(s32, s32);
#elif TVTYPE_PAL
void SCREEN_DIMENSIONS_set(s32, s32, s32, s32);
#endif
/*<0x80012F0C, 0x80012E7C, 0x80012E1C, 0x80012E1C>*/ void SOUND_MODE_unk1_set(s16);
/*<0x80012F34, 0x80012EA4, 0x80012E44, 0x80012E44>*/ void SOUND_MODE_unk2_set(s32, s16);

/*<0x80106790, 0x80100FB8, 0x8010BDE8, 0x8010BC28>*/ Object *fn_ois_get_object(OIS *ois);
/*<0x80100094, 0x800FAB54, 0x80105984, 0x801057C4>*/ void   *fn_Object_privStorPtr_get(Object *, u32 idx);

/*<0x800A9BA0, 0x800A8440, 0x800B3180, 0x800B3090>*/ void tmt_gameover_orchestrate_UNK(u32, u32, u32);
/*<0x800A9C50, 0x800A849C, 0x800B31DC, 0x800B30EC>*/ void jiggywiggy_return_from_puzzle(void);
/*<0x800A9B8C, 0x800A842C, 0x800B316C, 0x800B307C>*/ void jiggywiggy_map_store_temple_in_temp_map_flags(u16 map, u16 exit);
/*<0x800D1864, 0x800CF064, 0x800D9DD4, 0x800D9CB4>*/ void CONSUMABLE_change_held_count(u32, u32, u32);
/*<0x800D0A9C, 0x800CE29C, 0x800D900C, 0x800D8EEC>*/ bool ITEM_is_spawned(u32, u32);
/*<0x800D0B68, 0x800CE368, 0x800D90D8, 0x800D8FB8>*/ s32  SPECIAL_ITEM_collected_status(u32, SPECIAL_ITEM);
/*<0x800D0C78, 0x800CE478, 0x800D91E8, 0x800D90C8>*/ void SPECIAL_ITEM_JIGGIES_collected_set(u32, u32, u32);
/*<0x800D1338, 0x800CEB38, 0x800D98A8, 0x800D9788>*/ s32  JINJO_calc_collected_count(JINJO_COLOUR colour);
/*<0x800D129C, 0x800CEA9C, 0x800D980C, 0x800D96EC>*/ s32  JINJO_get_max_count(JINJO_COLOUR colour);
/*<0x80016DA0, 0x80016C60, 0x80016C90, 0x80016C90>*/ void ASSET_load_music_track(s32, u32);
/*<0x80017764, 0x800175D4, 0x80017604, 0x80017604>*/ bool fn_80017778(u32);

//- nulls
/*<0x800A9B84, 0x800A8424, 0x800B3164, 0x800B3074>*/ void null_800A9B84(void);


#endif // __FUNCTIONS_H__
