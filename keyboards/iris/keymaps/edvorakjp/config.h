#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 100

#define MOUSEKEY_WHEEL_MAX_SPEED   10
#define MOUSEKEY_WHEEL_TIME_TO_MAX 20

#define TAPPING_TERM 120
#define SWAP_SCLN

#endif
