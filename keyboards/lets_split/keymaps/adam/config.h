#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define _MASTER_RIGHT
#define EE_HANDS

#ifdef SUBPROJECT_rev2
    /* RGB Underglow */
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 8
#endif

#undef TAPPING_TERM
#define TAPPING_TERM 200 //At 500 some bad logic takes hold
#define PREVENT_STUCK_MODIFIERS
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

#endif