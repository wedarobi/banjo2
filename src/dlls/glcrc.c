#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"


// transform seed (in mips3 file)
extern u32 fn_crc_transform_seed(u64 *seed);


static void calc_checksum(void *start, void *end, u32 checksum[2])
{
    u8 *p;

    u32 shift = 0;

    u64 seed = 0x8F809F473108B3C1;

    u32 crc1 = 0;
    u32 crc2 = 0;

    u32 tmp;

    // CRC1: Iterate forwards over bytes
    for (p = start; (void *)p < end; p++)
    {
        seed += *p << (shift & 15);

        tmp = fn_crc_transform_seed(&seed);

        shift += 7;

        crc1 ^= tmp;
    }

    // CRC2: Iterate backwards over bytes
    for (p = (u8 *)end - 1; (void *)p >= start; p--)
    {
        seed += *p << (shift & 15);

        tmp = fn_crc_transform_seed(&seed);

        shift += 3;

        crc2 ^= tmp;
    }

    checksum[0] = crc1;
    checksum[1] = crc2;
}

u32 DLL_glcrc_00_crc_calc_and_update(u8 *data, s32 len)
{
    u32 *checksumPtr = (u32 *)(data + len) - 2;

    calc_checksum(data, checksumPtr, checksumPtr);

    return checksumPtr[0];
}

u32 DLL_glcrc_01_crc_calc_and_validate(u8 *data, s32 len)
{
    u32  calculated[2];
    u32 *checksum = (u32 *)(data + len) - 2;

    calc_checksum(data, checksum, calculated);

    return checksum[0] != calculated[0] || checksum[1] != calculated[1]
        //# Failed: returns some strange constant
        ? 0x6E382
        //# Success
        : 0;
}



