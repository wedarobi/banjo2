#ifndef __TYPES_H__
#define __TYPES_H__

#include "include/2.0L/PR/ultratypes.h"

typedef u8  BYTE;
typedef u16 HALF;
typedef u32 WORD;

typedef int bool;

typedef u32 MODEL; //!
typedef u32 FORM; //!
typedef u32 MS; //!
// typedef u32 ASSET; //!

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} tuple_f;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} tuple_u32;


#endif // __TYPES_H__
