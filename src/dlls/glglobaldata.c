#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/dlls.h"


#define SIZE_GLOBAL_EEP_AREA (0x80)

#define HEADER_MAGIC_INVALID (0x00)
#define HEADER_MAGIC_VALID   (0x08)



typedef void (*SaveFn)(s32 *, void **);

static SaveFn saveFns[] =
{
    SAVEDATA_get_FB4_size_and_addr,
    SAVEDATA_get_minigame_scores_size_and_addr,
};

//# useless function that does nothing
void DLL_glglobaldata_00_useless(void)
{
    s32 i;
    s32 offset = 1;

    for (i = 0; i < ARRLEN(saveFns); i++)
    {
        s32   datalen;
        void *dataptr;

        saveFns[i](&datalen, &dataptr);

        //! Debug stuff removed perhaps?

        offset += datalen;
    }
}

bool DLL_glglobaldata_01_if_global_data_header_valid(u8 *data)
{
    return data[0] == HEADER_MAGIC_VALID;
}

void DLL_glglobaldata_02_load_global_data_into_memory(u8 *src)
{
    s32 i;
    s32 offset = 1;

    for (i = 0; i < ARRLEN(saveFns); i++)
    {
        s32   datalen;
        void *dataptr;

        saveFns[i](&datalen, &dataptr);

        fn_memcpy(dataptr, src + offset, datalen);

        offset += datalen;
    }
}

static void write_global_savedata_header(u8 *data, s32 *currOffset)
{
    data[*currOffset] = HEADER_MAGIC_VALID;

    *currOffset = *currOffset + 1;
}

void DLL_glglobaldata_03_prepare_global_data_for_save(u8 *data)
{
    s32 i;
    s32 offset;

    DLL_glglobaldata_04_clear_global_data(data);
    offset = 0;

    write_global_savedata_header(data, &offset);

    for (i = 0; i < ARRLEN(saveFns); i++)
    {
        s32   datalen;
        void *dataptr;

        saveFns[i](&datalen, &dataptr);

        fn_memcpy(data + offset, dataptr, datalen);

        offset += datalen;
    }

    DLL_glcrc_00_crc_calc_and_update(data, SIZE_GLOBAL_EEP_AREA);
}

void DLL_glglobaldata_04_clear_global_data(char *dst)
{
    s32 i;

    for (i = 0; i < SIZE_GLOBAL_EEP_AREA; i++)
        dst[i] = 0;
}



