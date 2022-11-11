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

void fn_rom_fetch_WORD(u32 addr, u32 *dst);

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

/*<0x80014ED4, 0x80014EE4, 0x80014E44, 0x80014E44>*/ Framebuffer *FRAMEBUFFER_get_computing(void);
/*<0x8001DB90, 0x8001D288, 0x8001D2B8, 0x8001D2B8>*/ void FRAMEBUFFER_8001DB90(Framebuffer *, s32, s32, void *);
/*<0x8001D3D8, 0x8001CAD8, 0x8001CB08, 0x8001CB08>*/ void DEBUGGER_printf_at_pos(s32 x, s32 y, char *f, ...);
/*<0x8001D37C, 0x8001CA7C, 0x8001CAAC, 0x8001CAAC>*/ void DEBUGGER_printf(char *f, ...);
/*<0x8001E7A0, 0x8001DE20, 0x8001DE50, 0x8001DE50>*/ u32  DEBUGGER_fn_8001E7A0(u32);
/*<0x8001DDA4, 0x8001D474, 0x8001D4A4, 0x8001D4A4>*/ OSThread *THREAD_get_by_idx(s32 threadIdx);
/*<0x8001D98C, 0x8001D08C, 0x8001D0BC, 0x8001D0BC>*/ void fn_8001D98C(u32);

/*<0x800DABF0, 0x800D7E68, 0x800E2C38, 0x800E2AD8>*/ void SAVEDATA_get_FB4_size_and_addr(s32 *dstSize, void **dstAddr);
/*<0x800D21B0, 0x800CF930, 0x800DA6A0, 0x800DA580>*/ void SAVEDATA_get_minigame_scores_size_and_addr(s32 *dstSize, void **dstAddr);

/*<0x800D2054, 0x800CF7D4, 0x800DA544, 0x800DA424>*/ void minigame_highscore_set(u32, u32, u32);
/*<0x800D3E14, 0x800D1554, 0x800DC2F4, 0x800DC1C4>*/ u32  CHEAT_available_get(u32);
/*<0x800FC6B0, 0x800F7170, 0x80101FA0, 0x80101DE0>*/ void MUSIC_play_sfx_2_bgm(MUSIC);
/*<0x800FE844, 0x800F92E0, 0x80104110, 0x80103F50>*/ void gMusicObj_playThroughLz_set(u32);
/*<0x800FE734, 0x800F91D0, 0x80104000, 0x80103E40>*/ void gMusicObj_0x17_set(u32);
/*<0x800A9BA0, 0x800A8440, 0x800B3180, 0x800B3090>*/ void tmt_gameover_orchestrate_UNK(u32, u32, u32);
/*<0x800A9C50, 0x800A849C, 0x800B31DC, 0x800B30EC>*/ void jiggywiggy_return_from_puzzle(void);
/*<0x800A9B8C, 0x800A842C, 0x800B316C, 0x800B307C>*/ void jiggywiggy_map_store_temple_in_temp_map_flags(u16 map, u16 exit);
/*<0x800D1864, 0x800CF064, 0x800D9DD4, 0x800D9CB4>*/ void CONSUMABLE_change_held_count(u32, u32, u32);
/*<0x800D0A9C, 0x800CE29C, 0x800D900C, 0x800D8EEC>*/ bool ITEM_is_spawned(u32, u32);
/*<0x800D0B68, 0x800CE368, 0x800D90D8, 0x800D8FB8>*/ s32  SPECIAL_ITEM_collected_status(u32, SPECIAL_ITEM);
/*<0x800D0C78, 0x800CE478, 0x800D91E8, 0x800D90C8>*/ void SPECIAL_ITEM_JIGGIES_collected_set(u32, u32, u32);
/*<0x800D1338, 0x800CEB38, 0x800D98A8, 0x800D9788>*/ s32  JINJO_calc_collected_count(JINJO_COLOUR colour);
/*<0x800D129C, 0x800CEA9C, 0x800D980C, 0x800D96EC>*/ s32  JINJO_get_max_count(JINJO_COLOUR colour);

//- nulls
/*<0x800A9B84, 0x800A8424, 0x800B3164, 0x800B3074>*/ void null_800A9B84(void);


#endif // __FUNCTIONS_H__
