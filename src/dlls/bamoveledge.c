#include "include/2.0L/ultra64.h"

#include "include/functions.h"

#include "include/struct/player.h"


extern void func_8009BC08       (PlayerObj *, Vec3f *);
extern void fn_player_vel_cpy   (PlayerObj *, Vec3f *);
extern f32  fn_gamespeed_get    (void);
extern void fn_vec_scale        (Vec3f *, f32);
extern void fn_vec_add_direct   (Vec3f *, Vec3f *);
extern void func_8009B98C       (PlayerObj *, Vec3f *);


u32 DLL_bamoveledge_00(void)
{
    return 4;
}


void DLL_bamoveledge_01(u32 a0)
{

}

void DLL_bamoveledge_02(u32 a0)
{

}

void DLL_bamoveledge_03(PlayerObj *b)
{
    Vec3f v1;
    Vec3f v2;

    func_8009BC08(b, &v2);
    fn_player_vel_cpy(b, &v1);
    fn_vec_scale(&v1, fn_gamespeed_get());
    fn_vec_add_direct(&v2, &v1);
    func_8009B98C(b, &v2);
}




