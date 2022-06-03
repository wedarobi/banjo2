#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "include/2.0L/PR/ultratypes.h"

void func_800C3FC0(u32, f32, u32);
void func_800C9BB4(f32, u32, f32, u32);




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
