#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "include/2.0L/PR/ultratypes.h"

#include "include/struct/object.h"
#include "include/struct/player.h"

#include "include/enum/flag.h"
#include "include/enum/map.h"

void func_800C3FC0(u32, f32, u32);
void func_800C9BB4(f32, u32, f32, u32);


u32   func_800B2840(void);
u32   func_800B2344(u32);
void *func_800B27A0(void *);
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


/* ADDRv(0x8001ACCC, 0x8001A6BC, 0x8001A6EC, 0x8001A6EC) */ void *fn_malloc_temp(u32 size);
/**
 * [type]
 *   0 : temporary
 *   1 : permanent
 *   2 : unk
 */
/* ADDRv(0x8001ACEC, 0x8001A6DC, 0x8001A70C, 0x8001A70C) */ void *fn_malloc     (u32 size, u32 type);
/* ADDRv(0x8001B084, 0x8001AA74, 0x8001AAA4, 0x8001AAA4) */ void  fn_free       (void *ptr);





#endif // __FUNCTIONS_H__
