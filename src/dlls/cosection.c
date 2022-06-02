#include "include/2.0L/ultra64.h"

#include "include/enum/map.h"


/**
 * This sets the bootmap to Spiral Mountain,
 * probably for convenience during development.
 * 
 * This function is removed in non-USA versions.
 */
MAP DLL_cosection_00_get_dev_bootmap(void)
{
    return MAP_0AF_SM_MAIN_AREA;
}

MAP DLL_cosection_01_get_retail_bootmap(void)
{
    return MAP_18B_INTRO_SCREEN;
}



