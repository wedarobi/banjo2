#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"




// TODO: Handle compiler complaining about u8* vs char*, signedness changes matchingness

static char *threadNames[] =
{
/* 0 */ "VI",
/* 1 */ "IDLE",
/* 2 */ "TIDY",
/* 3 */ "CIC-6105",
/* 4 */ "AUDIO",
/* 5 */ "SCHEDULER",
/* 6 */ "MAIN",
/* 7 */ "JOY",
/* 8 */ "MOTOR",
/* 9 */ "CRASH",
};

void DLL_gzthread_00_thread_name_get(OSId threadIdx, u8 *dst)
{
    // WARN: cleanup, it's just a simple string copy

    u8 *s = (u8 *)threadNames[threadIdx];

    u8 c = *s++;

    *dst++ = c;

    while (c)
    {
        c = *s;

        *dst = c;

        dst++;
        s++;
    }
}

// TODO
void DLL_gzthread_01_print_page_THREADS(s32 a0, s32 a1, s32 a2, void *a3)
{

}





