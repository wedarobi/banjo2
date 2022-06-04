#include "include/2.0L/ultra64.h"

#include "include/functions.h"
#include "include/variables.h"
#include "include/struct/object.h"

#include "include/hacks/helpers.h"


void *fn_Object_privStorPtr_get(Object *, u32 idx); // 0x80100094, 0x800FAB54, 0x80105984, 0x801057C4



static void fn_priv_12(Object *o);


static AIDS aids_00 =
{
    0x343,
    0x287,
    0x8D9,
    1,
    (void *)VER_SWITCH(0x8011A2C0, 0x80114580, 0x8011F3B0, 0x8011F1F0),
    (void *)VER_SWITCH(0x80085828, 0x80084EC8, 0x8008FB18, 0x8008FB18),
    (void *)VER_SWITCH(0x80105834, 0x80100104, 0x8010AF34, 0x8010AD74),
    (void *)VER_SWITCH(0x80101870, 0x800FC260, 0x80107090, 0x80106ED0),
    0,
    0,
    0,
    0,
    0,
/* 0x20 */
    0,
    0,
    0x00000888,
    NULL,
    (void *)VER_SWITCH(0x800857E0, 0x80084E80, 0x8008FAD0, 0x8008FAD0),
    0,
    0,
    (void *)0,
    (void *)VER_SWITCH(0x80107C2C, 0x8010244C, 0x8010D27C, 0x8010D0BC),
    0x80002000,
    (void *)0,
    0,
};



struct struct_unk00
{
    s32 a;
    f32 b;
    f32 c;
};


//! the "00" here in the name refers to it belonging to "aids00"
struct chcoderoombits_00_privStor00
{
/* hex        */
// /* 000 >>>>>> */ BYTE UNK_000[0x154];

    struct struct_unk00 UNK_000[0x154 / 0x0C];
}; // size: 0x154



struct CheatInfo
{
    char *cheatStr;
    u8    UNK_04;
    u8    UNK_05;
    u8    UNK_06;
    u8    UNK_07;
    u8    UNK_08;
    u8    cheatIdx;
    u8    isPrefixCheato; // bool
    u8    UNK_0B;
};

static struct CheatInfo cheatArr[] =
{
/*   0 */ { "IPWNBZ",            0, 0, 0, 0x00, 0x00, 0x00, FALSE, 0 }, // CHEATO
/*   1 */ { "CWNBPWDQ",          0, 1, 0, 0x01, 0x11, 0x50, FALSE, 0 }, // FEATHERS
/*   2 */ { "WSSQ",              0, 1, 0, 0x02, 0x11, 0x51, FALSE, 0 }, // EGGS
/*   3 */ { "CNYYGDZZC",         0, 1, 0, 0x03, 0x11, 0x52, FALSE, 0 }, // FALLPROOF
/*   4 */ { "PZKWFENIH",         0, 1, 0, 0x04, 0x11, 0x53, FALSE, 0 }, // HONEYBACK
/*   5 */ { "AXHWEZU",           0, 1, 0, 0x05, 0x11, 0x54, FALSE, 0 }, // JUKEBOX
/*   6 */ { "SWBAOSSF",          0, 1, 0, 0x06, 0x11, 0x55, FALSE, 0 }, // GETJIGGY
/*   7 */ { "PZVOKS",            0, 1, 0, 0x0C, 0x11, 0x62, FALSE, 0 }, // HOMING
/*   8 */ { "QXGWDENKAZ",        0, 1, 0, 0x07, 0x11, 0x56, TRUE,  0 }, // SUPERBANJO
/*   9 */ { "QXGWDENTTF",        0, 1, 0, 0x08, 0x11, 0x57, TRUE,  0 }, // SUPERBADDY
/*  10 */ { "PZKWFHOKS",         0, 1, 0, 0x09, 0x11, 0x58, TRUE,  0 }, // HONEYKING
/*  11 */ { "KWQBHOKS",          0, 1, 0, 0x0A, 0x11, 0x59, TRUE,  0 }, // NESTKING
/*  12 */ { "QDWPBNWC",          0, 1, 0, 0x01, 0x11, 0x50, TRUE,  0 }, // SREHTAEF
/*  13 */ { "QSSW",              0, 1, 0, 0x02, 0x11, 0x51, TRUE,  0 }, // SGGE
/*  14 */ { "CZZDGYYNC",         0, 1, 0, 0x03, 0x11, 0x52, TRUE,  0 }, // FOORPLLAF
/*  15 */ { "HINEFWKZP",         0, 1, 0, 0x04, 0x11, 0x53, TRUE,  0 }, // KCABYENOH
/*  16 */ { "UZEWHXA",           0, 1, 0, 0x05, 0x11, 0x54, TRUE,  0 }, // XOBEKUJ
/*  17 */ { "FSSOABWS",          0, 1, 0, 0x06, 0x11, 0x55, TRUE,  0 }, // YGGIJTEG
/*  18 */ { "SKOVZP",            0, 1, 0, 0x0C, 0x11, 0x62, TRUE,  0 }, // GNIMOH
/*  19 */ { "AOSSFJOSSFQGWIONY", 0, 1, 0, 0x0B, 0x11, 0x5F, TRUE,  0 }, // JIGGYWIGGYSPECIAL
/*  20 */ { "INQBYOQB",          0, 2, 0, 0x85, 0x11, 0x60, TRUE,  0 }, // CASTLIST
/*  21 */ { "GYNFOBNSNOKQZK",    0, 3, 0, 0x00, 0x11, 0x61, TRUE,  0 }, // PLAYITAGAINSON
/*     */ { NULL,                0, 0, 0, 0x00, 0x00, 0x00, FALSE, 0 },
};




AIDS *DLL_chcoderoombits_00(void)
{
    return &aids_00;
}

static void fn_priv_00(Object *o)
{

}

static void fn_priv_01(Object *o)
{

}

static void fn_priv_02(Object *o, s32 interactionType, s32 a2)
{

}

// $a1: dialogId / assetId / fileId, whatever
static void fn_priv_03(Object *o, s32 dialogId)
{

}

/*static*/ void fn_priv_04(Object *o)
{
    void *p1 = fn_Object_privStorPtr_get(o, 0);
    void *p2 = fn_Object_privStorPtr_get(o, 0);

    u16 *p3 = (u16 *)((s32)p2 + 0x154);

    struct CheatInfo *c = cheatArr;

    for (; c->cheatStr != NULL; c++)
        *p3++ = 0;

    *(u8 *)((s32)p1 + 0x19) = 0;

    fn_priv_12(o);
}

static void fn_priv_05(Object *o, char *a1)
{

}

static void fn_priv_06(Object *o, struct CheatInfo *a1)
{

}

/*static*/ void fn_priv_07(Object *o)
{
    void *p1 = fn_Object_privStorPtr_get(o, 0);

    u16 *p3 = (u16 *)((s32)p1 + 0x154);

    void *p2 = fn_Object_privStorPtr_get(o, 0);

    struct CheatInfo *c = cheatArr;

    *p3 = 0;

    *(u8 *)((s32)p2 + 0x19) = 0;

    for (; c->cheatStr != NULL; c++, p3++)
        if (c->isPrefixCheato)
            *p3 = 0;
}

/*static*/ void fn_priv_08(Object *o)
{
    void *p1 = fn_Object_privStorPtr_get(o, 0);

    u16 *p3 = (u16 *)((s32)p1 + 0x154);

    struct CheatInfo *c = cheatArr;

    for (; c->cheatStr != NULL; c++, p3++)
        if (!c->isPrefixCheato)
            *p3 = 0;
}

void DLL_chcoderoombits_01(s32 a0, s32 a1)
{

}

static void fn_priv_09(s32 a0, s32 a1)
{

}

static void fn_priv_10(Object *o)
{

}



/*static*/ void fn_priv_11(Object *o, s32 a1)
{
    struct chcoderoombits_00_privStor00
        *p = fn_Object_privStorPtr_get(o, 0);

    switch (p->UNK_000[a1 + 3].a)
    {
        case 1: break;
        case 2: break;
        case 3:
        {
            f32 v = (0.6f - p->UNK_000[a1 + 2].c) / 0.6f;

            p->UNK_000[a1 + 3].a = 1;
            p->UNK_000[a1 + 2].c = v * 0.2f;

            break;
        }
        case 0:
        {
            p->UNK_000[a1 + 3].a = 1;
            p->UNK_000[a1 + 2].c = 0;

            break;
        }
    }
}

static void fn_priv_12(Object *o)
{
    s32 i;

    struct chcoderoombits_00_privStor00
        *p = fn_Object_privStorPtr_get(o, 0);

    for (i = 0; i < 26; i++)
    {
        switch (p->UNK_000[i + 3].a)
        {
            case 0: break;
            case 1:
            {
                f32 v = (0.2f - p->UNK_000[i + 2].c) / 0.2f;

                p->UNK_000[i + 3].a = v * 0.6f;

                break;
            }
            case 2:
            {
                p->UNK_000[i + 3].a = 3;
                p->UNK_000[i + 2].c = 0;

                break;
            }
            case 3: break;
        }
    }

}
void DLL_chcoderoombits_02(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp10)
{

}

extern s32 func_800D3E14(s32); // cheat_available_get

/*static*/ s32 get_cheat_available_count(void)
{
    s32 count;
    s32 i;

    count = 0;

    for (i = 1; i < 0xD; i++)
        if (func_800D3E14(i))
            count++;

    return count;
}











