#include "include/2.0L/ultra64.h"

#include "include/functions.h"

#include "include/struct/player.h"




void DLL_badronemem_00(Bo *b, u32 size)
{
    b->TransformObj = fn_malloc_temp(size);
}


void DLL_badronemem_01(Bo *b)
{
    fn_free(b->TransformObj);
    b->TransformObj = NULL;
}

void DLL_badronemem_02(u32 a0)
{

}

void DLL_badronemem_03(Bo *b)
{
    b->TransformObj = NULL;
}




