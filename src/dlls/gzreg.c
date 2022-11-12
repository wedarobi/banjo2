#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"

#include "include/dlls.h"


struct DebugInfo
{
    u32   mask;
    u32   val;
    char *str;
};

#define TRIPLE(x) { (x), (x), #x }
#define ARR_END { 0, 0, "" }

static struct DebugInfo debugInfo_RDP[] =
{
/*  0 */ TRIPLE(DPC_STATUS_XBUS_DMEM_DMA),
/*  1 */ TRIPLE(DPC_STATUS_FREEZE),
/*  2 */ TRIPLE(DPC_STATUS_FLUSH),
/*  3 */ TRIPLE(DPC_STATUS_START_GCLK),
/*  4 */ TRIPLE(DPC_STATUS_TMEM_BUSY),
/*  5 */ TRIPLE(DPC_STATUS_PIPE_BUSY),
/*  6 */ TRIPLE(DPC_STATUS_CMD_BUSY),
/*  7 */ TRIPLE(DPC_STATUS_CBUF_READY),
/*  8 */ TRIPLE(DPC_STATUS_DMA_BUSY),
/*  9 */ TRIPLE(DPC_STATUS_END_VALID),
/* 10 */ TRIPLE(DPC_STATUS_START_VALID),
/* 11 */ ARR_END
};

static struct DebugInfo debugInfo_RSP[] =
{
/*  0 */ TRIPLE(SP_STATUS_HALT),
/*  1 */ TRIPLE(SP_STATUS_BROKE),
/*  2 */ TRIPLE(SP_STATUS_DMA_BUSY),
/*  3 */ TRIPLE(SP_STATUS_DMA_FULL),
/*  4 */ TRIPLE(SP_STATUS_IO_FULL),
/*  5 */ TRIPLE(SP_STATUS_SSTEP),
/*  6 */ TRIPLE(SP_STATUS_INTR_BREAK),
/*  7 */ TRIPLE(SP_STATUS_YIELD),
/*  8 */ TRIPLE(SP_STATUS_YIELDED),
/*  9 */ TRIPLE(SP_STATUS_TASKDONE),
/* 10 */ TRIPLE(SP_STATUS_SIG3),
/* 11 */ TRIPLE(SP_STATUS_SIG4),
/* 12 */ TRIPLE(SP_STATUS_SIG5),
/* 13 */ TRIPLE(SP_STATUS_SIG6),
/* 14 */ TRIPLE(SP_STATUS_SIG7),
/* 15 */ ARR_END
};

static struct DebugInfo debugInfo_CAUSE[] =
{
/*  0 */ { CAUSE_BD,      CAUSE_BD,    "BD"                                              },
/*  1 */ { CAUSE_IP8,     CAUSE_IP8,   "IP8"                                             },
/*  2 */ { CAUSE_IP7,     CAUSE_IP7,   "IP7"                                             },
/*  3 */ { CAUSE_IP6,     CAUSE_IP6,   "IP6"                                             },
/*  4 */ { CAUSE_IP5,     CAUSE_IP5,   "IP5"                                             },
/*  5 */ { CAUSE_IP4,     CAUSE_IP4,   "IP4"                                             },
/*  6 */ { CAUSE_IP3,     CAUSE_IP3,   "IP3"                                             },
/*  7 */ { CAUSE_SW2,     CAUSE_SW2,   "IP2"                                             },
/*  8 */ { CAUSE_SW1,     CAUSE_SW1,   "IP1"                                             },
/*  9 */ { CAUSE_EXCMASK, EXC_INT,     "Interrupt"                                       },
/* 10 */ { CAUSE_EXCMASK, EXC_MOD,     "TLB modification exception"                      },
/* 11 */ { CAUSE_EXCMASK, EXC_RMISS,   "TLB exception on load or instruction fetch"      },
/* 12 */ { CAUSE_EXCMASK, EXC_WMISS,   "TLB exception on store"                          },
/* 13 */ { CAUSE_EXCMASK, EXC_RADE,    "Address error on load or instruction fetch"      },
/* 14 */ { CAUSE_EXCMASK, EXC_WADE,    "Address error on store"                          },
/* 15 */ { CAUSE_EXCMASK, EXC_IBE,     "Bus error exception on instruction fetch"        },
/* 16 */ { CAUSE_EXCMASK, EXC_DBE,     "Bus error exception on data reference"           },
/* 17 */ { CAUSE_EXCMASK, EXC_SYSCALL, "System call exception"                           },
/* 18 */ { CAUSE_EXCMASK, EXC_BREAK,   "Breakpoint exception"                            },
/* 19 */ { CAUSE_EXCMASK, EXC_II,      "Reserved instruction exception"                  },
/* 20 */ { CAUSE_EXCMASK, EXC_CPU,     "Coprocessor unusable exception"                  },
/* 21 */ { CAUSE_EXCMASK, EXC_OV,      "Arithmetic overflow exception"                   },
/* 22 */ { CAUSE_EXCMASK, EXC_TRAP,    "Trap exception"                                  },
/* 23 */ { CAUSE_EXCMASK, EXC_VCEI,    "Virtual coherency exception on intruction fetch" },
/* 24 */ { CAUSE_EXCMASK, EXC_FPE,     "Floating point exception (see fpcsr)"            },
/* 25 */ { CAUSE_EXCMASK, EXC_WATCH,   "Watchpoint exception"                            },
/* 26 */ { CAUSE_EXCMASK, EXC_VCED,    "Virtual coherency exception on data reference"   },
/* 27 */   ARR_END
};

static struct DebugInfo debugInfo_SR[] =
{
/*  0 */ { SR_CU3,      SR_CU3,     "CU3" },
/*  1 */ { SR_CU2,      SR_CU2,     "CU2" },
/*  2 */ { SR_CU1,      SR_CU1,     "CU1" },
/*  3 */ { SR_CU0,      SR_CU0,     "CU0" },
/*  4 */ { SR_RP,       SR_RP,      "RP"  },
/*  5 */ { SR_FR,       SR_FR,      "FR"  },
/*  6 */ { SR_RE,       SR_RE,      "RE"  },
/*  7 */ { SR_BEV,      SR_BEV,     "BEV" },
/*  8 */ { SR_TS,       SR_TS,      "TS"  },
/*  9 */ { SR_SR,       SR_SR,      "SR"  },
/* 10 */ { SR_CH,       SR_CH,      "CH"  },
/* 11 */ { SR_CE,       SR_CE,      "CE"  },
/* 12 */ { SR_DE,       SR_DE,      "DE"  },
/* 13 */ { SR_IBIT8,    SR_IBIT8,   "IM8" },
/* 14 */ { SR_IBIT7,    SR_IBIT7,   "IM7" },
/* 15 */ { SR_IBIT6,    SR_IBIT6,   "IM6" },
/* 16 */ { SR_IBIT5,    SR_IBIT5,   "IM5" },
/* 17 */ { SR_IBIT4,    SR_IBIT4,   "IM4" },
/* 18 */ { SR_IBIT3,    SR_IBIT3,   "IM3" },
/* 19 */ { SR_IBIT2,    SR_IBIT2,   "IM2" },
/* 20 */ { SR_IBIT1,    SR_IBIT1,   "IM1" },
/* 21 */ { SR_KX,       SR_KX,      "KX"  },
/* 22 */ { SR_SX,       SR_SX,      "SX"  },
/* 23 */ { SR_UX,       SR_UX,      "UX"  },
/* 24 */ { SR_KSU_MASK, SR_KSU_USR, "USR" },
/* 25 */ { SR_KSU_MASK, SR_KSU_SUP, "SUP" },
/* 26 */ { SR_KSU_MASK, SR_KSU_KER, "KER" },
/* 27 */ { SR_ERL,      SR_ERL,     "ERL" },
/* 28 */ { SR_EXL,      SR_EXL,     "EXL" },
/* 29 */ { SR_IE,       SR_IE,      "IE"  },
/* 30 */   ARR_END
};

static struct DebugInfo debugInfo_FP[] =
{
/*  0 */ { FPCSR_FS,      FPCSR_FS,    "FS"                      },
/*  1 */ { FPCSR_C,       FPCSR_C,     "C"                       },
/*  2 */ { FPCSR_CE,      FPCSR_CE,    "Unimplemented operation" },
/*  3 */ { FPCSR_CV,      FPCSR_CV,    "Invalid operation"       },
/*  4 */ { FPCSR_CZ,      FPCSR_CZ,    "Division by zero"        },
/*  5 */ { FPCSR_CO,      FPCSR_CO,    "Overflow"                },
/*  6 */ { FPCSR_CU,      FPCSR_CU,    "Underflow"               },
/*  7 */ { FPCSR_CI,      FPCSR_CI,    "Inexact operation"       },
/*  8 */ { FPCSR_EV,      FPCSR_EV,    "EV"                      },
/*  9 */ { FPCSR_EZ,      FPCSR_EZ,    "EZ"                      },
/* 10 */ { FPCSR_EO,      FPCSR_EO,    "EO"                      },
/* 11 */ { FPCSR_EU,      FPCSR_EU,    "EU"                      },
/* 12 */ { FPCSR_EI,      FPCSR_EI,    "EI"                      },
/* 13 */ { FPCSR_FV,      FPCSR_FV,    "FV"                      },
/* 14 */ { FPCSR_FZ,      FPCSR_FZ,    "FZ"                      },
/* 15 */ { FPCSR_FO,      FPCSR_FO,    "FO"                      },
/* 16 */ { FPCSR_FU,      FPCSR_FU,    "FU"                      },
/* 17 */ { FPCSR_FI,      FPCSR_FI,    "FI"                      },
/* 18 */ { FPCSR_RM_MASK, FPCSR_RM_RN, "RN"                      },
/* 19 */ { FPCSR_RM_MASK, FPCSR_RM_RZ, "RZ"                      },
/* 20 */ { FPCSR_RM_MASK, FPCSR_RM_RP, "RP"                      },
/* 21 */ { FPCSR_RM_MASK, FPCSR_RM_RM, "RM"                      },
/* 22 */   ARR_END
};



static void print_enabled_bits(u32 val, char *name, struct DebugInfo *info)
{
    bool toSkipComma = TRUE;

    DEBUGGER_printf("%s: x%08X ", name, val);
    DEBUGGER_printf("<");

    while (info->mask)
    {
        if ((val & info->mask) == info->val)
        {
            if (toSkipComma)
                toSkipComma = FALSE;
            else
                DEBUGGER_printf(",");

            DEBUGGER_printf("%s", info->str);
        }

        info++;
    }

    DEBUGGER_printf(">\n");
}

static void safe_sprint_float(char *dst, f32 val)
{
    switch (DEBUGGER_get_float_error_type(val))
    {
        case 0:
            fn_8002DC20(dst, "S.NaN");
            break;
        case 1:
            fn_8002DC20(dst, "Q.NaN");
            break;
        case 2:
            fn_8002DC20(dst, "+ve INF");
            break;
        case 3:
            fn_8002DC20(dst, "-ve INF");
            break;
        case 4:
        case 5:
        case 8:
        case 9:
            fn_8002DC20(dst, "%.6e", val);
            break;
        case 6:
        case 7:
            fn_8002DC20(dst, "%d", *(u32 *)&val);
            break;
    }
}

void DLL_gzreg_00_print_page_REGISTERS(OSThread *t)
{
    u32 pad;

    __OSThreadContext *ctx = &t->context;

    char cbuf1[0x10], cbuf2[0x10], cbuf3[0x10];


    DEBUGGER_printf("pc:x%08X\n", ctx->pc);

    print_enabled_bits(ctx->cause, "cause", debugInfo_CAUSE);
    DEBUGGER_printf("\n");

    DEBUGGER_printf("at:x%08X v0:x%08X v1:x%08X a0:x%08X\n", (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1, (u32)ctx->a0);
    DEBUGGER_printf("a1:x%08X a2:x%08X a3:x%08X t0:x%08X\n", (u32)ctx->a1, (u32)ctx->a2, (u32)ctx->a3, (u32)ctx->t0);
    DEBUGGER_printf("t1:x%08X t2:x%08X t3:x%08X t4:x%08X\n", (u32)ctx->t1, (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    DEBUGGER_printf("t5:x%08X t6:x%08X t7:x%08X s0:x%08X\n", (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7, (u32)ctx->s0);
    DEBUGGER_printf("s1:x%08X s2:x%08X s3:x%08X s4:x%08X\n", (u32)ctx->s1, (u32)ctx->s2, (u32)ctx->s3, (u32)ctx->s4);
    DEBUGGER_printf("s5:x%08X s6:x%08X s7:x%08X t8:x%08X\n", (u32)ctx->s5, (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    DEBUGGER_printf("t9:x%08X gp:x%08X sp:x%08X s8:x%08X\n", (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp, (u32)ctx->s8);

    DEBUGGER_printf("ra:x%08X %s          badvaddr:x%08X\n", (u32)ctx->ra, "          ", (u32)ctx->badvaddr);
    DEBUGGER_printf("\n");

    print_enabled_bits(ctx->fpcsr, "fpcsr", debugInfo_FP);
    DEBUGGER_printf("\n");

    safe_sprint_float(cbuf1, ctx->fp0.f.f_even);
    safe_sprint_float(cbuf2, ctx->fp2.f.f_even);
    safe_sprint_float(cbuf3, ctx->fp4.f.f_even);
    DEBUGGER_printf("f0  %-13s f2  %-13s f4  %-13s\n", cbuf1, cbuf2, cbuf3);
    safe_sprint_float(cbuf1, ctx->fp6.f.f_even);
    safe_sprint_float(cbuf2, ctx->fp8.f.f_even);
    safe_sprint_float(cbuf3, ctx->fp10.f.f_even);
    DEBUGGER_printf("f6  %-13s f8  %-13s f10 %-13s\n", cbuf1, cbuf2, cbuf3);
    safe_sprint_float(cbuf1, ctx->fp12.f.f_even);
    safe_sprint_float(cbuf2, ctx->fp14.f.f_even);
    safe_sprint_float(cbuf3, ctx->fp16.f.f_even);
    DEBUGGER_printf("f12 %-13s f14 %-13s f16 %-13s\n", cbuf1, cbuf2, cbuf3);
    safe_sprint_float(cbuf1, ctx->fp18.f.f_even);
    safe_sprint_float(cbuf2, ctx->fp20.f.f_even);
    safe_sprint_float(cbuf3, ctx->fp22.f.f_even);
    DEBUGGER_printf("f18 %-13s f20 %-13s f22 %-13s\n", cbuf1, cbuf2, cbuf3);
    safe_sprint_float(cbuf1, ctx->fp24.f.f_even);
    safe_sprint_float(cbuf2, ctx->fp26.f.f_even);
    safe_sprint_float(cbuf3, ctx->fp28.f.f_even);
    DEBUGGER_printf("f24 %-13s f26 %-13s f28 %-13s\n", cbuf1, cbuf2, cbuf3);
    safe_sprint_float(cbuf1, ctx->fp30.f.f_even);
    DEBUGGER_printf("f30 %-13s\n", cbuf1);
    DEBUGGER_printf("\n");

    print_enabled_bits(ctx->sr, "sr", debugInfo_SR);
}

void DLL_gzreg_01(void)
{
    DEBUGGER_printf("RDP current = 0x%08X   (0x%016llx) \n", IO_READ(DPC_CURRENT_REG) + K0BASE, *(u64 *)(IO_READ(DPC_CURRENT_REG) + K0BASE));
    DEBUGGER_printf("RDP start   = 0x%08X   (0x%016llx) \n", IO_READ(DPC_START_REG)   + K0BASE, *(u64 *)(IO_READ(DPC_START_REG)   + K0BASE));
    DEBUGGER_printf("RDP end     = 0x%08X   (0x%016llx) \n", IO_READ(DPC_END_REG)     + K0BASE, *(u64 *)(IO_READ(DPC_END_REG)     + K0BASE));

    print_enabled_bits(IO_READ(DPC_STATUS_REG), "\nRDP status:", debugInfo_RDP);
    print_enabled_bits(IO_READ(SP_STATUS_REG),  "\nRSP status:", debugInfo_RSP);

    DEBUGGER_printf("\nFree memory was %d bytes.\n", HEAP_get_occupied_size());
}

#if VERSION_USA
u32 DLL_gzreg_02(OSThread *t)
{
    return t->context.pc;
}
#endif




