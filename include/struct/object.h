#pragma once

#include "include/types.h"


#if 0
typedef struct GenericArrHeader {
/* 0x00 */ u32            slotSize; // always 0x9C ?
/* 0x04 */ struct Object* first;
/* 0x08 */ struct Object* last;
/* 0x0C */ void*          UNKPTR_0x0C;
} GenericArrHeader;

typedef struct GenericSimpleArrHeader {
    u16 slotSize;
    u16 length;
} GenericSimpleArrHeader;

typedef struct Object {
/* 0x00 */ struct ObjIdStruct* ObjIdStruct;
/* 0x04 */ Vec3f               position;
// TODO: change to func, change in ml_bto and snooie
/* 0x10 */ void               *AIDS_getter;
/* 0x14 >>> */ WORD UNK_0x14;
/* 0x18 >>> */ WORD UNK_0x18;
/* 0x1C */ union {
    WORD UNK_0x1C;
    u32 nestCyclerId;

    //! modloader: BtOnline info for arbdata arb spawn
    // (triggering jinjo/jiggy circling around puppet)
    // TODO: move to ml_bto
    struct {
        // The idx of the puppet to animate the collected item around
        u8  puppetIdx;
        u8  : 8;
        // Only set after puppetIdx is validated
        u16 signature;
    } btoJinjo;
};

/* 0x20 >>> */ WORD UNK_0x20;
/* 0x24 >>> */ BYTE UNK_0x24;
/* 0x25 >>> */ BYTE UNK_0x25;
/* 0x26 >>> */ BYTE UNK_0x26;
/* 0x27 >>> */ BYTE UNK_0x27;
/* 0x28 */ f32                 animationTimer;
/* 0x2C */ union {
    /*
     * 0x201/0x200 solo b in toxic waste uses this word to determine
     * who can press the switch Object
     */
    u32 formBitfield;
    /* note nest stores rotation speed float here */
    f32 NoteNest_rotSpeed;
};
/* 0x30 >>> */ BYTE UNK_0x30;
/* 0x31 >>> */ BYTE UNK_0x31;
/* 0x32 >>> */ BYTE UNK_0x32;
/* 0x33 >>> */ BYTE UNK_0x33;
/* 0x34 >>> */ BYTE UNK_0x34;
/* 0x35 >>> */ BYTE UNK_0x35;
/* 0x36 >>> */ BYTE UNK_0x36;
/* 0x37 >>> */ BYTE UNK_0x37;
/* 0x38 */ f32                 scale;
/* 0x3C */ struct ObjIdStruct *ObjIdStruct_2; //? what for?
/* 0x40 */ struct Object      *shadowObject;
/* 0x44 */ union {
    struct {
        // Rot_ vars: backwards compat
        f32 RotX;
        f32 RotY;
        f32 RotZ;
    };
    struct {
        f32 pitch;
        f32 yaw;
        f32 roll;
    };
    Vec3f rotation;
};
/* 15.0f for shoes, f32 trunc'd to int for jiggies (jiggy collected idx) */
/* 0x50 */ f32 UNK_0x50;
/* 0x54 */ f32 UNK_0x54;
/* 0x58 */ f32 UNK_0x58;
/* 0x5C >>> */ BYTE UNK_0x5C;
/* 0x5D >>> */ BYTE UNK_0x5D;
/* 0x5E */ u8                  health; //?
/* 0x5F >>> */ BYTE UNK_0x5F;
/* 0x60 */ u16 UNK_0x60;
/* 0x62 >>> */ BYTE UNK_0x62;
/* 0x63 >>> */ BYTE UNK_0x63;
/* 0x64 >>> */ BYTE UNK_0x64;
/* 0x65 >>> */ union {
    BYTE UNK_0x65;
    struct {
        u8 : 3;
        /* warp silo colour: 0 red, 1 green */
        u8 warpSiloUnlocked : 1;
        u8 : 4;
    };
};
/* 0x66 >>> */ BYTE UNK_0x66;
/* 0x67 >>> */ BYTE UNK_0x67;
/* 0x68 >>> */ BYTE UNK_0x68;
/* 0x69 >>> */ BYTE UNK_0x69;
/* 0x6A >>> */ BYTE UNK_0x6A;
/* 0x6B >>> */ BYTE UNK_0x6B;
/* 0x6C >>> */ union {
    WORD UNK_0x6C;
    struct {
        u32 : 11;
        ACTOR actorIdx         : 12;
        // Used by jinjo to store jinjo specialIdx
        u32   specialIdx_JINJO : 9;
    };

    //! modloader: BtOnline puppet info
    // TODO: Move into ml_bto
    WORD bto_storage;
    struct {
        u8  puppetIdx;
        struct {
            u8 b7 : 1;
            u8 b6 : 1;
            u8 b5 : 1;
            u8 b4 : 1;
            u8 b3 : 1;
            u8 b2 : 1;
            u8 fadingOut : 1;
            u8 fadingIn  : 1;
        } infoBitfield;
        u16 sig;
    } bto;
};
/* 0x70 */ union {
    struct {
        /*
        * Indexes arr pointed to by 8012AE84
        * Subtract 1 to get the real idx
        * Elm size: 0x1C
        */
        u32 MapSetup_UnkIdx : 7;
        u32 : 15;
        /*
        * Used to index the MapSetupObjArr
        * (pointed to by 8012AF60)
        * Subtract 1 to get the real idx
        * Elm size: 0x18
        */
        u32 MapSetup_Idx : 6;
        u32 : 4;
    };
    struct {
        BYTE UNK_0x70;
        BYTE UNK_0x71;
        union {
            u16 movementState; //?
            struct {
                u16 animationCounter : 6;
                u16 : 10;
            };
        };
    };
};
/* 0x74 */ struct {
    u8 BIT_7 : 1;
    // warp pad clear bug
    u8 BIT_6 : 1;
    // jj move silo green
    u8 moveSiloUnlocked : 1;
    u8 BIT_4 : 1;
    u8 BIT_3 : 1;
    u8 BIT_2 : 1;
    u8 BIT_1 : 1;
    u8 BIT_0 : 1;
} arbBitfield;
/* 0x75 */ union {
    BYTE UNK_0x75;
    struct {
        u8 : 6;
        /* arbBitfield_Shadow - set flag for shadow? */
        u8 : 1;
        u8 : 1;
    };
};
/* 0x76 >>> */ BYTE UNK_0x76;
/* 0x77 >>> */ BYTE UNK_0x77;
/* 0x78 >>> */ BYTE UNK_0x78;
/*
 * for warp pads, this is set to 1, which increments opacity
 * until 0xFF with subaddiefade, then set to 0
 */
/* 0x79 */ u8 UNK_0x79;
/* 0x7A >>> */ BYTE UNK_0x7A;
/* 0x7B >>> */ BYTE UNK_0x7B;
/* 0x7C >>> */ BYTE UNK_0x7C;
/* 0x7D >>> */ BYTE UNK_0x7D;
/* 0x7E >>> */ BYTE UNK_0x7E;
/* 0x7F >>> */ BYTE UNK_0x7F;
/* 0x80 >>> */ BYTE UNK_0x80;
/* 0x81 >>> */ BYTE UNK_0x81;
/* 0x82 */ u16 tmpStorageIndices[5];
/* 0x8C */ u8                  animationIdx;
/* 0x8D >>> */ BYTE UNK_0x8D;
/* 0x8E >>> */ BYTE UNK_0x8E;
/* 0x8F >>> */ BYTE UNK_0x8F;
/* 0x90 >>> */ BYTE UNK_0x90;
/* 0x91 >>> */ BYTE UNK_0x91;
/* 0x92 >>> */ BYTE UNK_0x92;
/* 0x93 >>> */ BYTE UNK_0x93;
/* 0x94 >>> */ BYTE UNK_0x94;
/* 0x95 >>> */ BYTE UNK_0x95;
/* 0x96 >>> */ BYTE UNK_0x96;
/* 0x97 >>> */ BYTE UNK_0x97;
/* 0x98 */ u8                  filterRed;
/* 0x99 */ u8                  filterGreen;
/* 0x9A */ u8                  filterBlue;
/* 0x9B */ u8                  opacity;
} Object; // 0x9C

typedef struct ObjIdStruct {
/* 0x00 >>> */ void* PTR_0x00;
/* 0x04 >>> */ void* PTR_0x04;
/* 0x08 >>> */ void* PTR_0x08;
/* 0x0C >>> */ BYTE  UNK_0x0C;
/* 0x0D >>> */ BYTE  UNK_0x0D;
/* 0x0E >>> */ BYTE  UNK_0x0E;
/* 0x0F >>> */ BYTE  UNK_0x0F;

// when 0x20, jinjo targets player with head. When 0x00, jinjo faces straight ahead
/* 0x10 >>> */ s16   UNK_0x10;

/* 0x12 >>> */ u16   UNK_0x12;
/* 0x14 */ MODEL modelIdx : 16;

// stores [jinjo colour idx + 0xC31]
// game reads this to draw the right colour on the Jinjo Object when it enters the camera view
/* 0x16 >>> */ u16  UNK_0x16;

/* 0x18 >>> */ BYTE  UNK_0x18;
/* 0x19 */ u8  UNK_0x19;
/* 0x1A */ u16 idxInObjectArr : 11;
/*      */ u16 UNK_0x1A_b2 : 5;
/* 0x1C >>> */ BYTE  UNK_0x1C;
/* 0x1D >>> */ BYTE  UNK_0x1D;
/* 0x1E >>> */ BYTE  UNK_0x1E;
/* 0x1F >>> */ BYTE  UNK_0x1F;
/* 0x20 >>> */ BYTE  UNK_0x20;
/* 0x21 >>> */ BYTE  UNK_0x21;
/* 0x22 >>> */ BYTE  UNK_0x22;
/* 0x23 >>> */ BYTE  UNK_0x23;
/* 0x24 */ enum AIDX aidx : 10;
/*      >>> */ u16 : 6;
/* 0x26 >>> */ BYTE  UNK_0x26;
/* 0x27 >>> */ BYTE  UNK_0x27;

// u16, control jinjo facing angle when targeting player?
/* 0x28 >>> */ BYTE  UNK_0x28;
/* 0x29 >>> */ BYTE  UNK_0x29;

/* 0x2A */ u16  UNK_0x2A;
/* 0x2C >>> */ BYTE  UNK_0x2C;
/* 0x2D >>> */ BYTE  UNK_0x2D;
/* 0x2E >>> */ BYTE  UNK_0x2E;
/* 0x2F >>> */ BYTE  UNK_0x2F;
} ObjIdStruct;
#endif


typedef struct AIDS
{
/* 0x00 */ /*enum AIDX */ u16 aidx     : 16;
/* 0x02 */ /*enum ACTOR*/ u16 actorIdx : 16;
/* 0x04 */ /*enum MODEL*/ u16 modelIdx : 16;
/* 0x06 */ u16    spawnAnimOffset;
/* 0x08 */ void  *animListPtr;
/* 0x0C */ void (*fn_update)(void *);
/* 0x10 */ void (*fn_cutscene)(void *);
/* 0x14 */ void (*fn_draw)(void *);
/* 0x18 */ BYTE   field_0x18;
/* 0x19 */ BYTE   field_0x19;
/* 0x1A */ BYTE   field_0x1a;
/* 0x1B */ BYTE   field_0x1b;
/* 0x1C */ f32    shadowScale;
/* 0x20 */ /*FLAG*/ u16 despawnFlag;
/* 0x22 */ HALF   field_0x22;
/* 0x24 */ u32    bitfield2;
/* 0x28 */ void (*field_0x28)(void *);
/* 0x2C */ void (*field_0x2C)(void *);
/* 0x30 */ u16    tmpStorageLen1;
/* 0x32 */ u16    tmpStorageLen2;
/* 0x34 */ void (*fn_init)(void *);
/* 0x38 */ struct Object *(*fn_alloc)(void);
/* 0x3C */ u32    bitfield;
/* 0x40 */ void (*fn_interaction)(void *);
/* 0x44 */ WORD   field_0x44;
} AIDS;


