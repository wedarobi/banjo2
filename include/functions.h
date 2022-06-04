#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "include/2.0L/PR/ultratypes.h"

#include "include/struct/object.h"
#include "include/struct/player.h"

void func_800C3FC0(u32, f32, u32);
void func_800C9BB4(f32, u32, f32, u32);


u32   func_800B2840(void);
u32   func_800B2344(u32);
void *func_800B27A0(void *);
void  fn_memcpy_fast(void *, void *, u32);

void func_8009BC08       (PlayerObj *, Vec3f *);
void fn_player_vel_cpy   (PlayerObj *, Vec3f *);
f32  fn_gamespeed_get    (void);
void fn_vec_scale        (Vec3f *, f32);
void fn_vec_add_direct   (Vec3f *, Vec3f *);
void func_8009B98C       (PlayerObj *, Vec3f *);


/* -> fxkern */
s32  fn_font_char_visual_width_get(s32, u8);
void fn_currFont_set(s32);
void fn_currFont_reset_params(void);
void fn_currFont_size_set(f32);
void fn_gfx_head_printing(Gfx **);
void fn_gfx_tail_printing(Gfx **);
void fn_gfx_print_char(Gfx **, s32, s32, u8);
















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
