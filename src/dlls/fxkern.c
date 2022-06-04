#include "include/2.0L/ultra64.h"

#include "include/functions.h"


//! double check, and hoist
#define FRAMEBUFFER_WIDTH  (304)
#define FRAMEBUFFER_HEIGHT (216)


extern s32  fn_font_char_visual_width_get(s32, u8);
extern void fn_currFont_set(s32);
extern void fn_currFont_reset_params(void);
extern void fn_currFont_size_set(f32);
extern void fn_gfx_head_printing(Gfx **);
extern void fn_gfx_tail_printing(Gfx **);
extern void fn_gfx_print_char(Gfx **, s32, s32, u8);

static struct
{
    // match with curr letter
    u8 char1;
    // match with next letter
    u8 char2;
    s8 offsetMultiplyFactor1;
    s8 offsetMultiplyFactor2;
}
spacings[] =
{
    {'A',  'V', -3,  0 },
    {'W',  'A', -3,  0 },
    {'V',  'A', -3,  0 },
    {'Y',  'A', -2,  0 },
    {'M',  'O', -1,  0 },
    {'D',  'A', -1,  0 },
    {'R',  'O', -2,  0 },
    {'T',  'A', -2,  0 },
    {'S',  'T', -1,  0 },
    {'A',  'M', -1,  0 },
    {'C',  'O', -1,  0 },
    {'O',  'V', -1,  0 },
    {'L',  'O', -1,  0 },
    {'M',  'U', -1,  0 },
    {'U',  'M', -1,  0 },
    {'M',  'A', -2,  0 },
    {'M',  '0', -1,  0 },
    {'H',  'I',  1,  0 },
    {'I',  'P',  1,  0 },
    {'E',  'E',  0,  1 },
    {'Z',  'E',  0, -1 },
    {'*',  'S',  1,  0 },
    {'*',  '\'', 3,  0 },
#if VERSION_EUR
    {'*',  '.',  4,  0 },
    {'*',  ',',  3,  0 },
#endif
    {'\0', '\0', 0,  0 },
};

#if !VERSION_JPN
static void get_spacing_correction_offsets(u8 nextLetter, u8 currLetter, s32 *omf1, s32 *omf2)
{
    s32 i;

    *omf2 = 0;
    *omf1 = 0;

    // Loop until no more match objects to test against
    for (i = 0; spacings[i].char1; i++)
    {
        if (spacings[i].char2 == nextLetter &&
            // '*' is used as a placeholder for "any character"
           (spacings[i].char1 == currLetter || spacings[i].char1 == '*'))
        {
            // We found a matching pair. Give correction offsets to the parent function
            *omf1 = spacings[i].offsetMultiplyFactor1;
            *omf2 = spacings[i].offsetMultiplyFactor2;

            return;
        }
    }
}
#endif


#define FontType_TOTALS 1

static f32 letterSpacing;

static struct
{
    f32 offsetX;
    f32 offsetY;
} letterOffsets[64];

static s32 calculate_incremental_letter_offsets(u8 *str)
{
    s32 i;

    letterOffsets[0].offsetX = 0;
    letterOffsets[0].offsetY = 0;

    for (i = 1; str[i] != '\0' && i != 64; i++)
    {
        s32 tmp1;
        s32 tmp2;
        s32 width;

        letterOffsets[i].offsetX = letterOffsets[i-1].offsetX;

        //# Takes half each of the vis widths of the curr and next letters
        //# and adds them both to the current offset

        width = fn_font_char_visual_width_get(FontType_TOTALS, str[i-1]);
        letterOffsets[i].offsetX += letterSpacing * (width / 2);

        width = fn_font_char_visual_width_get(FontType_TOTALS, str[i]);
        letterOffsets[i].offsetX += letterSpacing * (width / 2);

#if !VERSION_JPN
        //# Overlay the letters (move them slightly left)
        letterOffsets[i].offsetX += letterSpacing * -4.0f;

        //# Add spacing correction offsets
        get_spacing_correction_offsets(str[i], str[i-1], &tmp1, &tmp2);
        letterOffsets[i].offsetX += letterSpacing * tmp1;
        letterOffsets[i].offsetY  = letterSpacing * tmp2;
#endif
    }

    //# Return idx of last character
    return i - 1;
}

static void print(Gfx **dl, s32 x, s32 y, u8 *str, s32 lastIdx)
{
    fn_currFont_set(FontType_TOTALS);
    fn_gfx_head_printing(dl);

    for (; lastIdx >= 0; lastIdx--)
        fn_gfx_print_char(
            dl,
            x + letterOffsets[lastIdx].offsetX,
            y + letterOffsets[lastIdx].offsetY,
            str[lastIdx]
        );

    fn_gfx_tail_printing(dl);
}

#if VERSION_USA
void DLL_fxkern_00_totalsfont_print(Gfx **dl, s32 x, s32 y, u8 *str)
{
    s32 lastIdx = calculate_incremental_letter_offsets(str);
    print(dl, x, y, str, lastIdx);
}
#endif

void DLL_fxkern_01_totalsfont_print_centred(Gfx **dl, s32 y, u8 *str)
{
    s32 lastIdx = calculate_incremental_letter_offsets(str);
    print(dl, (FRAMEBUFFER_WIDTH - letterOffsets[lastIdx].offsetX) / 2, y, str, lastIdx);
}

void DLL_fxkern_02_totalsfont_size_reset(void)
{
    fn_currFont_reset_params();
    letterSpacing = 1;
}

void DLL_fxkern_03_totalsfont_size_set(f32 size)
{
    fn_currFont_size_set(size);
    letterSpacing = size;
}





