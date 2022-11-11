#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"

#include "include/dlls.h"



#define FB_PIXEL(r, g, b, a) \
    (((GPACK_RGBA5551((r),(g),(b),(a))) << 0x10) | (GPACK_RGBA5551((r),(g),(b),(a))))


/**
 * stall the cpu to preserve screen contents for a few seconds
 */
static void pause(void)
{
    s32 i;

    for (i = 0; i < 300; i++)
        func_80015778();
}

/**
 * Does the following
 * - Clears the screen
 * - Fills the background with a solid colour
 * - Draws the build date and thread name at the top
 */
// TODO stack only
static void prepare_new_screen(OSId threadIdx)
{
    char threadName[0x10];

    u32 month, day, time;
    u16 hour, minute;

    u32 buildInfoArea = (u32)&__BUILD_INFO_AREA;

    Framebuffer *fb = FRAMEBUFFER_get_active();

    //# Fill framebuffer with colour background
    fn_memset(fb, FB_PIXEL(0x10, 0x40, 0x80, 1), FRAMEBUFFER_get_size());

    fn_8001D96C();

    fn_rom_fetch_WORD(buildInfoArea + 0x1C, &month);
    fn_rom_fetch_WORD(buildInfoArea + 0x18, &day);
    fn_rom_fetch_WORD(buildInfoArea + 0x14, &time);

    //# [time] "22:40" is stored as decimal: 2240
    hour   = time / 100;
    minute = time - (hour * 100);

    DEBUGGER_printf_at_pos(34, 0, "Build: %02d:%02d %02d/%02d/00", hour, minute, day, month);

    DLL_gzthread_00_thread_name_get(threadIdx, threadName);
    DEBUGGER_printf_at_pos(0, 0, "Thread: %s", threadName);

    fn_8001D9CC(0, 3);
}

void DLL_gzpublic_00_debugger_main_window(OSThread *t)
{
    pause();
    FRAMEBUFFER_swap_to(FRAMEBUFFER_get_computing_idx());
    pause();

    while (TRUE)
    {
        //- Page 0: stack trace
        prepare_new_screen(t->id);
        DLL_gztrace_01(t, 0, 0, 0);
        FRAMEBUFFER_8001DA60(FRAMEBUFFER_get_active());
        pause();

        //- Page 1: registers
        prepare_new_screen(t->id);
        DLL_gzreg_00(t);
        FRAMEBUFFER_8001DA60(FRAMEBUFFER_get_active());
        pause();

        //- Page 2: thread info
        prepare_new_screen(t->id);
        DLL_gzthread_01_print_page_THREADS(-1);
        FRAMEBUFFER_8001DA60(FRAMEBUFFER_get_active());
        pause();

        //- Page 3: screen contents at moment of crash
        FRAMEBUFFER_swap_to(FRAMEBUFFER_get_computing_idx());
        pause();
        FRAMEBUFFER_swap_to(FRAMEBUFFER_get_computing_idx());
    }
}



