#ifndef __STRUCT_MUSIC__
#define __STRUCT_MUSIC__

#include "include/types.h"

struct InstrumentSetObj
{
    //# bitfield of which tracks/instruments to play in the current song
    u32 landSet;
    //# same as above, but used when underwater
    u32 underwaterSet;
    //# try not to go too high, it's a u16 but try stick to u8 bounds or the game will lag
    u16 landTempo;
    u16 underwaterTempo;
};

struct MusicObj
{
/* 00 */ f32  unk00;
/* 04 */ f32  unk04;
/* 08 */ s16  musicIdx;
/* 0A */ s16  unk0A;
//# the value of the lower 2 bits stored in the music struct array
/* 0C */ s16  UNK_musicIdxLower;
//# if 1 (sm <-> tunnel) or 2 (exiting jiggywiggy puzzle), this makes the game keep playing the music through the transition. 0 makes it fade out/in
/* 0E */ u8   playThroughLz;
/* 0F */ u8   unk0F;

//# game checks this upon surfacing and reverts music to normal theme
/* 10 */ u8   isUnderwater;
/* 11 */ u8   unk11;
/* 12 */ u8   unk12;
/* 13 */ u8   unk13;
/* 14 */ u8   unk14;
/* 15 */ u8   unk15;
/* 16 */ u8   unk16;
/* 17 */ u8   unk17;
/* 18 */ u8   unk18;
/* 19 */ BYTE pad19;
/* 1A */ BYTE pad1A;
/* 1B */ BYTE pad1B;
/* 1C */ WORD pad1C;

/* 20 */ HALF unk20;
//# changing during runtime works fine with fade out/in
/* 22 */ u16  instrumentSet;
/* 24 */ HALF pad24;
/* 26 */ BYTE pad26;
/* 27 */ BYTE pad27;
/* 28 */ s32  unk28;
/* 2C */ s32  unk2C;

/* 30 */ f32  unk30;
/* 34 */ BYTE unk34;
/* 35 */ BYTE unk35;
/* 36 */ HALF pad36;
/* 38 */ HALF pad38;
/* 3A */ BYTE pad3A;
/* 3B */ BYTE pad3B;
/* 3C */ f32  unk3C;

/* 40 */ u8   unk40;
/* 41 */ u8   unk41;
/* 42 */ u8   unk42;
/* 43 */ u8   unk43;
/* 44 */ struct InstrumentSetObj *instrumentSetPtr1;
/* 48 */ struct InstrumentSetObj *instrumentSetPtr2;
/* 4C */ f32  unk4C;

/* 50 */ u8   unk50;
/* 51 */ u8   unk51;
/* 52 */ u8   unk52;
/* 53 */ u8   unk53;
/* 54 */ u8   unk54;
/* 55 */ u8   unk55;
/* 56 */ u8   unk56;
/* 57 */ u8   unk57;
/* 58 */ u8   unk58;
/* 59 */ u8   unk59;
/* 5A */ u8   unk5A;
/* 5B */ u8   unk5B;
/* 5C */ u8   unk5C;
/* 5D */ u8   unk5D;
/* 5E */ u8   unk5E;
/* 5F */ BYTE pad5F;

/* 60 */ WORD pad60;
/* 64 */ WORD pad64;
/* 68 */ WORD pad68;
/* 6C */ BYTE pad6C;
/* 6D */ BYTE pad6D;
/* 6E */ BYTE pad6E;
/* 6F */ BYTE pad6F;

/* 70 */ f32  unk70;
/* 74 */ f32  unk74;
/* 78 */ BYTE pad78;
/* 79 */ BYTE pad79;
/* 7A */ BYTE pad7A;
/* 7B */ BYTE pad7B;
/* 7C */ u8   unk7C;
/* 7D */ u8   unk7D;
/* 7E */ u8   unk7E;
/* 7F */ u8   unk7F;

/* 80 */ WORD unk80;
/* 84 */ f32  unk84;
};





#endif // __STRUCT_MUSIC__




