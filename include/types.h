#ifndef __TYPES_H__
#define __TYPES_H__

#include "include/2.0L/PR/ultratypes.h"

#define TVTYPE_NTSC ((VERSION_USA) || (VERSION_JPN))
#define TVTYPE_PAL  ((VERSION_EUR) || (VERSION_AUS))

typedef u8  BYTE;
typedef u16 HALF;
typedef u32 WORD;

typedef int bool;

typedef u32 MODEL; //!
typedef u32 FORM; //!
typedef u32 MS; //!
// typedef u32 ASSET; //!

typedef struct { f32 x; f32 y; f32 z; } Vec3f;
typedef struct { u32 x; u32 y; u32 z; } Vec3u32;
typedef struct { s32 x; s32 y; s32 z; } Vec3s32;
typedef struct { u16 x; u16 y; u16 z; } Vec3u16;
typedef struct { s16 x; s16 y; s16 z; } Vec3s16;
typedef struct { s32 x; s32 y;        } Vec2s32;
typedef struct { s16 x; s16 y;        } Vec2s16;




#define FRAMEBUFFER_WIDTH  (304)
#if TVTYPE_NTSC
    #define FRAMEBUFFER_HEIGHT (228)
#elif TVTYPE_PAL
    #define FRAMEBUFFER_HEIGHT (268)
#endif

typedef struct
{
    u16 px[FRAMEBUFFER_HEIGHT][FRAMEBUFFER_WIDTH];
} Framebuffer;

// typedef u16 Framebuffer[FRAMEBUFFER_HEIGHT][FRAMEBUFFER_WIDTH];



#endif // __TYPES_H__
