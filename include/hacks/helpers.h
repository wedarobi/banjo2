#ifndef __HACKS_HELPERS_H__
#define __HACKS_HELPERS_H__



#if VERSION_USA
    #define VER_SWITCH(usa, jpn, eur, aus) (usa)
#elif VERSION_JPN
    #define VER_SWITCH(usa, jpn, eur, aus) (jpn)
#elif VERSION_EUR
    #define VER_SWITCH(usa, jpn, eur, aus) (eur)
#elif VERSION_AUS
    #define VER_SWITCH(usa, jpn, eur, aus) (aus)
#endif











#endif // __HACKS_HELPERS_H__
