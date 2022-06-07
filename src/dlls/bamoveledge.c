#include "include/2.0L/ultra64.h"

#include "include/functions.h"

#include "include/struct/player.h"



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

void DLL_bamoveledge_03(Bo *b)
{
    Vec3f v1;
    Vec3f v2;

    func_8009BC08(b, &v2);
    fn_player_vel_cpy(b, &v1);
    fn_vec_scale(&v1, fn_gamespeed_get());
    fn_vec_add_direct(&v2, &v1);
    func_8009B98C(b, &v2);
}




