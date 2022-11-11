#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"


static u8 *threadNames[] =
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

static u32 framebuffer_val_unk = 0xFF2020FF;



void DLL_gzthread_00_thread_name_get(OSId threadIdx, u8 *dst)
{
    // WARN: cleanup, it's just a simple string copy

    char *s = threadNames[threadIdx];

    char c = *s++;

    *dst++ = c;

    while (c)
    {
        c = *s;

        *dst = c;

        dst++;
        s++;
    }
}

// TODO s0 <-> s1
void DLL_gzthread_01_print_page_THREADS(s32 a0)
{
    s32 i;

    if (a0 >= 0)
    {
        a0 += 7;

        for (i = 0; i < 9; i++)
        {
            Framebuffer *fb = FRAMEBUFFER_get_computing();

            FRAMEBUFFER_8001DB90(fb, i, a0, &framebuffer_val_unk);
        }
    }

    DEBUGGER_printf_at_pos( 0,  5, "Thread");
    DEBUGGER_printf_at_pos(11, -1, "State");
    DEBUGGER_printf_at_pos(21, -1, "Pri");
    DEBUGGER_printf_at_pos(29, -1, "PC");
    DEBUGGER_printf_at_pos(38, -1, "SP");
    DEBUGGER_printf_at_pos(47, -1, "Queue\n\n");

    for (i = 0; i < ARRLEN(threadNames); i++)
    {
        OSThread *t = THREAD_get_by_idx(i);

        DEBUGGER_printf_at_pos(0, -1, "%s", threadNames[i]);

        fn_8001D98C(11);

        if (t != NULL)
        {
            u32 tmp0 = DEBUGGER_fn_8001E7A0(i);

            u32 pc = t->context.pc;
            u32 sp = t->context.sp;

            switch (t->state)
            {
                case OS_STATE_STOPPED:  DEBUGGER_printf("Stopped");  break;
                case OS_STATE_RUNNABLE: DEBUGGER_printf("Runnable"); break;
                case OS_STATE_RUNNING:  DEBUGGER_printf("Running");  break;
                case OS_STATE_WAITING:  DEBUGGER_printf("Waiting");  break;
            }

            DEBUGGER_printf_at_pos(21, -1, "%3d/%2d", tmp0, t->priority);
            DEBUGGER_printf_at_pos(29, -1, "%08X",    pc);
            DEBUGGER_printf_at_pos(38, -1, "%08X",    sp);

            if (t->state == OS_STATE_WAITING)
                DEBUGGER_printf_at_pos(47, -1, "%08X", t->queue);
            else
                DEBUGGER_printf("\n");
        }
        else
        {
            DEBUGGER_printf("(n/a)\n");
        }
    }
}





