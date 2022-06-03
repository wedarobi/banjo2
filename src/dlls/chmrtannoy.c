#include "include/2.0L/ultra64.h"

#include "include/functions.h"


#if 0
static u32 test_priv_fn(void)
{
    func_800C3FC0(0x3F9, 0.79f, 0x8000);
}

static void *ptr = &test_priv_fn;

static void test_pub_fn(u32 a0)
{
    switch (a0)
    {
        case 0:
        {
            func_800C3FC0(0x3E9, 0.75f, 0x7FFF);

            break;
        }
        case 1:
        {
            func_800C9BB4(0.2f, 0x3E9, 0.58f, 0x7FFF);

            break;
        }
        case 2:
        {
            func_800C9BB4(0.5f, 0x3E9, 0.58f, 0x7FFF);
            func_800C3FC0(0x3E9, 0.75f, 0x7FFF);

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
        {
            func_800C3FC0(0x420, 1.f, 0x7FFF);
            test_priv_fn();

            break;
        }
    }

    test_priv_fn();
}
#endif

void DLL_chmrtannoy_00(void)
{
    func_800C3FC0(0x3E9, 0.75f, 0x7FFF);
    func_800C9BB4(0.2f, 0x3E9, 0.58f, 0x7FFF);
}


