#include "include/2.0L/ultra64.h"

#include "include/functions.h"




s32 DLL_dbvtxnormal_00(s32 a0, s32 a1)
{
    return a0 + (a1 * 4);
}

#if VERSION_USA
void DLL_dbvtxnormal_01(void *a0)
{
    fn_free(a0);
}

void *DLL_dbvtxnormal_02(s32 *a0)
{
    void *dst;
    s32   size;
    void *src;

    size = func_800B2344(func_800B2840()) * 4;

    dst = fn_malloc_temp(size);
    src = func_800B27A0(a0);

    fn_memcpy_fast(dst, src, size);

    return dst;
}
#endif


