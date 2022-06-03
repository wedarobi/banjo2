#include "include/2.0L/ultra64.h"

#include "include/functions.h"

#include "include/struct/player.h"




void DLL_bastatemem_00(PlayerObj *b, u32 size)
{
    b->dynMsObj = fn_malloc_temp(size);
}


void DLL_bastatemem_01(PlayerObj *b)
{
    fn_free(b->dynMsObj);
    b->dynMsObj = NULL;
}

void DLL_bastatemem_02(u32 a0)
{

}

void DLL_bastatemem_03(PlayerObj *b)
{
    b->dynMsObj = NULL;
}




