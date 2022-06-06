#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"




void DLL_gcwater_00(void)
{
    s32 val = 0;

    void *p = func_800BEB28(1);

    if (p)
    {
        p = func_800B2720(p);

        if (p)
            val = func_800AAD80(p);
    }

    if (val == 0)
    {
        p = func_800BEB28(0);

        if (p)
        {
            p = func_800B2720(p);

            if (p)
                val = func_800AAD80(p);
        }
    }

    fn_flag_set(FLAG2_6B5_UNK, val ? TRUE : FALSE);
}




