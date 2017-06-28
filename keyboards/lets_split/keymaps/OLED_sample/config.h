#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_I2C
//#define USE_SERIAL

/* Select hand configuration */

#define MASTER_LEFT
// #define _MASTER_RIGHT
// #define EE_HANDS
#define FLIP_HALF

#define SSD1306OLED


#define PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#ifdef SUBPROJECT_rev1
    #include "../../rev1/config.h"
#endif
#ifdef SUBPROJECT_rev2
    #include "../../rev2/config.h"
#endif

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 6
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#endif