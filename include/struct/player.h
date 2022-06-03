#ifndef __STRUCT_PLAYER_H__
#define __STRUCT_PLAYER_H__

#include "include/types.h"


// #include "../types.h"
// #include "model.h"
// #include "enums.h"

// #define PACKED __attribute__ ((packed))
#define PACKED


//! We don't even need this animation shit so why am i filling it in?
//! Fill it in elsewhere, not in snooie you dumbass
//! Copy it in here when you know you might actually need it
typedef struct PO_Remote_AnimationObj {
    /* 0x00 */ f32 animTimer;
    /* 0x04 >>> */ BYTE PAD_0x04[0x4];
    /* 0x08 >>> */ f32  UNK_0x08;
    /* 0x0C */ f32  animSpeed;
    /* 0x10 >>> */ f32  UNK_0x10;
    /* 0x14 >>> */ f32  UNK_0x14;
    /* 0x18 */ u16 animationIdxCpy;
    /* 0x1A >>> */ BYTE UNK_0x1A;
    /* 0x1B >>> */ BYTE UNK_0x1B;
    /* 0x1C >>> */ BYTE PAD_0x1C[0x10];
    /* 0x2C >>> */ f32  UNK_0x2C;
    /* 0x30 >>> */ f32  UNK_0x30;
    /* 0x34 */ u16 animationIdx;
    /* 0x36 */ BYTE PAD2[0x6];
} PO_Remote_AnimationObj; // 0x3C

typedef struct Player_AnimationObj {
    /* 0x00 */ PO_Remote_AnimationObj* Remote_AnimationObj;
    /* 0x04 >>> */ WORD PAD_0x04;
    /* 0x08 */ u32     playerAnimating; //? undone on button input
    /* 0x0C */ u8      UNK_0x0C;
    /* 0x0D */ u8      UNK_0x0D;
    /* 0x0E */ u16     UNK_0x0E;
    /* 0x10 */ tuple_f UNK_0x10;
    /* 0x1C */ f32     UNK_0x1C;
    /* 0x20 */ f32     UNK_0x20;
    /* 0x24 */ f32     UNK_0x24;
    /* 0x28 */ f32     UNK_0x28;
    /* 0x2C */ tuple_f UNK_0x2C;
    /* 0x38 */ u8      UNK_0x38;
    /* 0x39 >>> */ u8 PAD_0x39;
    /* 0x3A >>> */ u8 PAD_0x3A;
    /* 0x3B >>> */ u8 PAD_0x3B;
    /* 0x3C*/  u32     UNK_0x3C;
} Player_AnimationObj; // 0x40

typedef struct Player_ZoomBtnObj {
    /* 0x00 */ u8 unk_0x00;
    /* 0x01 */ u8 unk_0x01;
               // zoom level with C-DOWN
    /* 0x02 */ u8 cBtnState;
    /* 0x03 */ u8 unk_0x03;
    /* 0x04 */ u8 unk_0x04;
    /* 0x05 */ u8 unk_0x05;
               // 0x02 when normal, 0x09 when in FPV?
    /* 0x06 */ u8 unk_0x06;
    /* 0x07 */ u8 unk_0x07;
} Player_ZoomBtnObj;

typedef struct Player_LockStateObj {
    /* 0x00 */ WORD  unk_0x00;
    /* 0x04 */ BYTE* unk_0x04;
    /* 0x08 */ WORD  unk_0x08;
    /* 0x0C */ union PACKED {
        MODEL modelIdx : 16; u16 modelIdx_;
    } UNION_0x0C;
    /* 0x0E */ HALF  unk_0x0C;
    /* 0x10 */ BYTE  unk_0x10;
    /* 0x11 */ BYTE  unk_0x11;
    /* 0x12 */ BYTE  unk_0x12;
    /* 0x13 */ BYTE  unk_0x13;
    /* 0x14 */ BYTE  unk_0x14;
    /* 0x15 */ BYTE  unk_0x15;
    /* 0x16 */ BYTE  unk_0x16;
    /* 0x17 */ BYTE  unk_0x17;
    /* 0x18 */ BYTE  unk_0x18;
    /* 0x19 */ u8    playerNotLocked;
    /* 0x1A */ BYTE  unk_0x1A;
    /* 0x1B */ BYTE  unk_0x1B;
    /* 0x1C */ f32   unk_0x1C;
} Player_LockStateObj; // len 0x20 (actually 0x118)

typedef struct MiscFlags_SplitFlags {
    // 1: BK, 2: splitInProgress, 3: split B/K, 4: joinInProgress
    // save/load checks this to try and not allow save/load during split/join
    // it doesnt seem to work on join when controlling a secondary character, but it doesnt seem to have any bad side effects anyhow
    u8 splitAnimationIdx;
    u8 standingOnSplitPad_asBK;
    u8 standingOnSplitPad_asSplitCharacter;
} MiscFlags_SplitFlags;

// Holds selected egg type, egg drawer animation state, etc
typedef struct Player_EggDrawerObj {
    /* 0x00 */ u8 currEggSetType;
               // currently selected egg index (0-4)
    /* 0x01 */ u8 eggIdx;
    /* 0x02 */ u8 Bitfield;
               // 0 for not shown, 1 for entering, 2 for open, 3 for closing?
    /* 0x03 */ u8 eggDrawerAnimStateIdx;
} Player_EggDrawerObj;

typedef struct Player_FpvReticleObj {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ struct {
        // 0: nil, 1: exited, 2: entered, 3: entering, 4: exiting
        u8 transitionState;
        u8 active;
        u8 : 8;
        u8 : 8;
    } STRUCT_0x08;
    /* 0x0C */ f32 transitionTimer;
    /* 0x10 */ struct {
        u8 : 8;
        u8 : 8;
        BYTE : 8;
        BYTE : 8;
    } STRUCT_0x10;
    /* 0x14 */ u32 opacity;
    /* 0x18 */ f32 scale;
} Player_FpvReticleObj; // 0x1C

typedef struct MiscFlags {
    /* 0x00 */ u8 : 8;
    /* 0x01 */ u8 onFlightPad;
    /* 0x02 */ u8 onShockSpringPad;
    /* 0x03 */ u8 inTalonTrot;
    /* 0x04 */ u8 : 8;
    /* 0x05 */ u8 hasUsedRatATatRap;
    /* 0x06 */ u8 : 8;
    /* 0x07 */ u8 : 8;
    /* 0x08 */ u8 : 8;
    /* 0x09 */ u8 : 8;
    /* 0x0A */ u8 shortBeakBarge;
    /* 0x0B */ u8 beakBarge;
    /* 0x0C */ u8 longBeakBarge;
    /* 0x0D */ u8 : 8;
    /* 0x0E */ u8 enteringWadingBoots1;
    /* 0x0F */ u8 enteringWadingBoots2; //? both flags are set at once
    /* 0x10 */ u8 enteringTurboTalonTrainers;
    /* 0x11 */ u8 : 8;
    /* 0x12 */ u8 hasUsedFlutter;
    /* 0x13 */ BYTE PAD0x13[0xD];
    /* 0x20 */ BYTE PAD0x20[0x9];
    /* 0x29 */ u8 usingRoll;
} MiscFlags;

typedef struct Player_FPInfoObj {
    /* 0x00 */ u32  bitfield_0x00;
    /* 0x04 >>> */ BYTE UNK_0x04;
    /* 0x05 >>> */ BYTE UNK_0x05;
    /* 0x06 >>> */ BYTE UNK_0x06;
    /* 0x07 >>> */ BYTE UNK_0x07;
    /* 0x08 >>> */ BYTE UNK_0x08;
    /* 0x09 >>> */ BYTE UNK_0x09;
    /* 0x0A >>> */ BYTE UNK_0x0A;
    /* 0x0B >>> */ BYTE UNK_0x0B;
    /* 0x0C >>> */ BYTE UNK_0x0C;
    /* 0x0D >>> */ BYTE UNK_0x0D;
    /* 0x0E >>> */ BYTE UNK_0x0E;
    /* 0x0F >>> */ BYTE UNK_0x0F;
        // 0x1: NORMAL_VIEW
        // 0x2: FIRST_PERSON_VIEW_EXITING_AND_FLIGHT
        // 0x3: FIRST_PERSON_VIEW
    /* 0x10 */ u8 fpViewState;
    /* 0x11 >>> */ BYTE UNK_0x11;
    /* 0x12 >>> */ BYTE UNK_0x12;
    /* 0x13 >>> */ BYTE UNK_0x13;
        // 0x0: NOT_FIRST_PERSON_MODE
        // 0x1: FIRST_PERSON_MODE_NO_AIM
        // 0x2: FIRST_PERSON_MODE_WITH_AIM
    /* 0x14 */ u8 eggAimState;
    /* 0x15 */ u8 ifEggAimOn;
    /* 0x16 */ u8 ifEggAimToggleable; //?
    /* 0x17 >>> */ BYTE UNK_0x17;
    //# amaze-o-gaze goggle zoom level (4.0f - 40.0f (range 36.0f), increments of 1.5f)
    /* 0x18 */ f32  zoomLevel;
} Player_FPInfoObj; // 0x1C

typedef struct Player_FloorObj {
    /* 0x00 >>> */ BYTE PAD[0x70];
    /* 0x70 */ f32 offsetY;
} Player_FloorObj;

typedef struct Player_SlopeObj {
    /* 0x00 >>> */ BYTE PAD_0x00[0x28];
    /* 0x28 */ union PACKED {
        FORM transformingInfo : 8; u8 transformingInfo_;
    } UNION_0x28;
    /* 0x29 */ union PACKED {
        FORM currentTrans : 8; u8 currentTrans_;
    } UNION_0x29;
    /* 0x2A >>> */ BYTE PAD_0x2A[0xE];
    /* 0x38 */ f32 slopeTimer;
    /* 0x3C >>> */ BYTE PAD_0x3C;
    /* 0x3D >>> */ BYTE PAD_0x3D;
    /* 0x3E >>> */ BYTE PAD_0x3E;
    /* 0x3F */ BYTE UNK_0x3F; //? @ 0x800A3544
    /* 0x40 >>> */ BYTE PAD_0x40[0x10];
    /* 0x50 */ BYTE UNK_0x50;
    /* 0x51 >>> */ BYTE PAD_0x51[0xF];
} Player_SlopeObj;

typedef struct Player_VelocityObj {
    /* 0x00 >>> */ BYTE PAD_0x00[0x10];
    /* 0x10 */ Vec3f velocity;
    /* 0x1C >>> */ BYTE PAD_0x1C[0x18];
    /* 0x34 */ f32 gravity;
    /* 0x38 */ f32 terminalVelocity;
    /* 0x3C */ BYTE PAD_0x3C[0x14];
    /* 0x50 */ f32 movementSpeedFactor;
    /* 0x54 */ u8 walkThroughDoorStatus;
    /* 0x55 */ u8 unk_0x55;
    /* 0x56 */ u8 unk_0x56;
    /* 0x57 */ u8 unk_0x57;
} Player_VelocityObj;

typedef struct Player_RotXObj {
    /* 0x00 */ f32 curr;
    /* 0x04 */ f32 target;
} Player_RotXObj;

typedef struct Player_PositionObj {
    /* 0x00 */ union {
        Vec3f     position1;
        tuple_u32 position1_u32;
    } UNION_0x00;
    /* 0x0C */ union {
        Vec3f     position2;
        tuple_u32 position2_u32;
    } UNION_0x0C;
    /* 0x18 */ union {
        Vec3f     position3;
        tuple_u32 position3_u32;
    } UNION_0x18;
} Player_PositionObj;

typedef struct Player_RotZObj {
    /* 0x00 */ f32 curr;
    /* 0x04 */ f32 target;
} Player_RotZObj;

typedef struct Player_RotYObj {
    /* 0x00 */  union {
        f32 facingAngle; // a.k.a. curr
        u32 facingAngle_u32;
    } UNION_0x00;
    /* 0x04 */ union {
        f32 movingAngle; // a.k.a. target
        u32 movingAngle_u32;
    } UNION_0x04;
} Player_RotYObj;

typedef struct Player_MovementStateObj {
    /* 0x00 */ MS prev;
    /* 0x04 */ MS curr;
    /* 0x08 */ WORD unk_0x08;
    /* 0x0C */ u16  lastCollisionIdx; // used in the collision switch @ 0x80099B94 USA
    /* 0x0E */ u16  unk_0x0E;
    /* 0x10 */ WORD pad_0x10;
} Player_MovementStateObj; // 0x14

typedef struct Player_GroundedObj {
    /* 0x00 */ bool isInWater;
    // touched water but haven't touched land yet
    /* 0x01 */ bool isWet;
    /* 0x02 */ bool isGrounded;
    /* 0x03 */ BYTE UNK_0x03;
} Player_GroundedObj;

typedef struct Player_ShoeInfoObj {
    /* 0x00 */ f32  shoeTimerBase;
    /* 0x04 */ u8   activeShoeType;
    /* 0x05 */ BYTE UNK_0x05;
    /* 0x06 */ BYTE UNK_0x06;
    /* 0x07 */ BYTE UNK_0x07;
    /* 0x08 */ WORD UNK_0x08;
    /* 0x0C */ WORD UNK_0x0C;
    /* 0x10 */ WORD UNK_0x10;
    /* 0x14 */ WORD UNK_0x14;
} Player_ShoeInfoObj;

/**
 * Dynamic size based on circumstance: this is a union
 * 
 * blaster     : 0x2A8
 * kazfly/fly  : 0x20
 * van         : 0x14
 * dronevanish : 0x1C
 */
typedef union Player_DynMsObj {
    BYTE PAD_0x00; //! placeholder
} Player_DynMsObj;

typedef struct Player_TransformObj {
    u8 field_0x0;
    u8 field_0x1;
    u8 field_0x2;
    u8 field_0x3;
    u8 field_0x4;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;
    u8 field_0x8;
    u8 field_0x9;
    u8 field_0xa;
    u8 field_0xb;
    f32 field_0xc;
    u8 field_0x10;
    u8 field_0x11;
    u8 field_0x12;
    u8 field_0x13;
    f32 field_0x14;
    f32 field_0x18;
    bool transformInProgress;
    u8 field_0x1d;
    u8 field_0x1e;
    u8 field_0x1f;
    u8 field_0x20;
    u8 field_0x21;
    u8 field_0x22;
    u8 field_0x23;
    u8 field_0x24;
    u8 field_0x25;
    u8 field_0x26;
    u8 field_0x27;
    f32 field_0x28;
    f32 field_0x2c;
    FORM field_0x30;
    FORM field_0x31;
    u8 currXformAnimStage; /* manages the stages of the transform animation */
    BYTE field_0x33;
    BYTE field_0x34;
    BYTE field_0x35;
    BYTE field_0x36;
    BYTE field_0x37;
    BYTE field_0x38;
    BYTE field_0x39;
    BYTE field_0x3a;
    BYTE field_0x3b;
    BYTE field_0x3c;
    BYTE field_0x3d;
    BYTE field_0x3e;
    BYTE field_0x3f;
    BYTE field_0x40;
    BYTE field_0x41;
    BYTE field_0x42;
    BYTE field_0x43;
    BYTE field_0x44;
    BYTE field_0x45;
    BYTE field_0x46;
    BYTE field_0x47;
    BYTE field_0x48;
    BYTE field_0x49;
    BYTE field_0x4a;
    BYTE field_0x4b;
    BYTE field_0x4c;
    BYTE field_0x4d;
    BYTE field_0x4e;
    BYTE field_0x4f;
    BYTE field_0x50;
    BYTE field_0x51;
    BYTE field_0x52;
    BYTE field_0x53;
    BYTE field_0x54;
    BYTE field_0x55;
    BYTE field_0x56;
    BYTE field_0x57;
    BYTE field_0x58;
    BYTE field_0x59;
    BYTE field_0x5a;
    BYTE field_0x5b;
    BYTE field_0x5c;
    BYTE field_0x5d;
    BYTE field_0x5e;
    BYTE field_0x5f;
    BYTE field_0x60;
    BYTE field_0x61;
    BYTE field_0x62;
    BYTE field_0x63;
    BYTE field_0x64;
    BYTE field_0x65;
    BYTE field_0x66;
    BYTE field_0x67;
    BYTE field_0x68;
    BYTE field_0x69;
    BYTE field_0x6a;
    BYTE field_0x6b;
    BYTE field_0x6c;
    BYTE field_0x6d;
    BYTE field_0x6e;
    BYTE field_0x6f;
} Player_TransformObj;

// psize: (hex) size padded to the next word
//  size: (hex) real size
typedef struct PlayerObj {
/* off | psize  size     FILE      */
/*  00 |   4      2 baalarm        */ void *UNK_0x000;
/*  04 |  40     40                */ Player_AnimationObj     *AnimationObj;
/*  08 |   8      8 baattach       */ void *UNK_0x008;
/*  0C |  1C     1C                */ void *UNK_0x00C;
/*  10 |   8      8 bababykaz      */ void *UNK_0x010;
/*  14 |  18     18 babackpack     */ void *UNK_0x014;
/*  18 |   4      1                */ void *UNK_0x018;
/*  1C |  20     20 babee          */ void *UNK_0x01C;
/*  20 |   C      C                */ void *UNK_0x020;
/*  24 |  1C     1C baboost        */ void *UNK_0x024;
/*  28 |  20     20 babounce       */ void *UNK_0x028;
/*  2C |  1C     1C                */ void *UNK_0x02C;
/*  30 |  18     18                */ void *UNK_0x030;
/*  34 |  18     18 babuzz         */ void *UNK_0x034;
/*  38 |  40     40                */ Player_ZoomBtnObj       *ZoomBtnObj;
/*  3C |  78     78                */ void *UNK_0x03C;
/*  40 |  28     28                */ void *UNK_0x040;
/*  44 |   8      8 bacough        */ void *UNK_0x044;
/*  48 |   4      4                */ void *UNK_0x048;
/*  4C |   4      1                */ void *UNK_0x04C;
/*  50 | 118    118                */ Player_LockStateObj     *LockStateObj;
/*  54 |  4C     4C badrone        */ void *UNK_0x054;
/*  58 |  14     14                */ MiscFlags_SplitFlags    *SplitFlags;
/*  5C |   C      C badust         */ void *UNK_0x05C;
/*  60 |   4      4 baeggaim       */ void *UNK_0x060;
/*  64 |   4      4                */ Player_EggDrawerObj     *EggDrawerObj;
/*  68 |  1C     1C baeggcursor    */ Player_FpvReticleObj    *FpvReticleObj;
/*  6C |  14     14 baeggfire      */ void *UNK_0x06C;
/*  70 |  28     28 baeggsetup     */ void *UNK_0x070;
/*  74 |  1C     1C                */ void *UNK_0x074;
/*  78 |  20     20                */ void *UNK_0x078;
/*  7C |  18     18                */ void *UNK_0x07C;
/*  80 |  44     42                */ MiscFlags               *MiscFlags;
/*  84 |  28     28 baflameline    */ void *UNK_0x084;
/*  88 |  10     10 baflamethrower */ void *UNK_0x088;
/*  8C |  10     10 bafly          */ void *UNK_0x08C;
/*  90 |  1C     1C bafpctrl       */ Player_FPInfoObj        *FirstPersonInfoObj;
/*  94 |  AC     AC                */ Player_FloorObj        **FloorObjPtr;
/*  98 |  28     28                */ void *UNK_0x098;
/*  9C |  10     10 bahold         */ void *UNK_0x09C;
/*  A0 |  58     58                */ Player_SlopeObj         *SlopeObj;
/*  A4 |   C      C                */ void *UNK_0x0A4;
/*  A8 |  7C     7C bainvisible    */ void *UNK_0x0A8;
/*  AC |  30     30                */ void *UNK_0x0AC;
/*  B0 |  20     20 bakaztorpedo   */ void *UNK_0x0B0;
/*  B4 |  14     14                */ void *UNK_0x0B4;
/*  B8 |   C      C                */ void *UNK_0x0B8;
/*  BC |  1C     1C                */ void *UNK_0x0BC;
/*  C0 |  F0     F0                */ void *UNK_0x0C0;
/*  C4 |  10      F                */ void *UNK_0x0C4;
/*  C8 |  C4     C4                */ Player_VelocityObj      *VelocityObj;
/*  CC |   4      4 bamoveledge    */ void *UNK_0x0CC;
/*  D0 |   8      8 bamum          */ void *UNK_0x0D0;
/*  D4 |   4      1                */ void *UNK_0x0D4;
/*  D8 |  20     20 bapackctrl     */ void *UNK_0x0D8;
/*  DC |  10     10                */ Player_RotXObj          *RotXObj;
/*  E0 |  34     34                */ void *UNK_0x0E0;
/*  E4 |  30     30                */ Player_PositionObj      *PositionObj;
/*  E8 |   C      C bapulse        */ void *UNK_0x0E8;
/*  EC |   4      4 bareact        */ void *UNK_0x0EC;
/*  F0 |  84     84                */ void *UNK_0x0F0;
/*  F4 |  10     10                */ Player_RotZObj          *RotZObj;
/*  F8 |  1C     1C                */ Player_RotYObj          *RotYObj;
/*  FC |   8      8                */ void *UNK_0x0FC;
/* 100 |   4      4 basetup        */ void *ShadowQ; //? shadow bool u8 @ 0x4C?
/* 104 |  20     20                */ void *UNK_0x104;
/* 108 |  10     10                */ void *UNK_0x108;
/* 10C |  18     18 bashoes        */ Player_ShoeInfoObj      *ShoeInfoObj;
/* 110 |  30     30 basnowball     */ void *UNK_0x110;
/* 114 |  F4     F4                */ void *UNK_0x114;
/* 118 |   8      8 baspin         */ void *UNK_0x118;
/* 11C |   C      C basquash       */ void *UNK_0x11C;
/* 120 |  14     14                */ Player_MovementStateObj *MovementStateObj;
/* 124 |   C      C                */ void *UNK_0x124;
/* 128 |  68     68                */ void *UNK_0x128;
/* 12C |   4      4                */ void *UNK_0x12C;
/* 130 |  6C     6C basub          */ void *UNK_0x130;
/* 134 |   8      8 baswim         */ void *UNK_0x134;
/* 138 |  18     18                */ void *UNK_0x138;
/* 13C |  78     78 batimer        */ void *UNK_0x13C;
/* 140 |  20     20 batranslate    */ void *UNK_0x140;
/* 144 |  18     18 bavan          */ void *UNK_0x144;
/* 148 |  14     14 bawandglow     */ void *UNK_0x148;
/* 14C |  34     34 bawasher       */ void *UNK_0x14C;
/* 150 |  14     14                */ Player_GroundedObj      *GroundedObj;
/* 154 | ???     20 bawobble       */ void *UNK_0x154;

//- end pointer array, start initial player data

/* 158 >>> */ WORD PAD_0x158;
            // increases with every idle animation, and loops back around once all are played
/* 15C */ u32 currentIdleAnimationCounter;
/* 160 */ u32 UNK_0x160;
/* 164 */ u32 UNK_0x164;
/* 168 */ u32 UNK_0x168;
/* 16C */ f32 UNK_0x16C; //? [bswalk       @ 0x314] [lwc1 $f4, 0x16C($t6=>PlayerObj*)] read on walk
/* 170 */ f32 UNK_0x170; //? [bsbbilldrill @ 0x6B0] [lwc1 $f6, 0x170($a0=>PlayerObj*)] read on beak bust
/* 174 */ BYTE PAD_0x174[0x8];
/* 17C */ u32 playerVisible;
/* 180 */ u32 playerFrozen;
            // Index of this player object. Solo K's is usually 1
/* 184 */ u32 currPlayerIdx;
/* 188 */ Player_DynMsObj *dynMsObj;
/* 18C */ Player_TransformObj *TransformObj;
/* 190 */ BYTE PAD_0x190[0x0C];
/* 19C END */
// ^ this is the address that the first Player_ ptr points to, so we assume it's the end of the main struct
} PlayerObj;



#endif // __STRUCT_PLAYER_H__
