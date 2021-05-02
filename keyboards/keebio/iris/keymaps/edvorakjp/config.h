#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SWAP_SCLN
#define TAPPING_TERM 300
#define IGNORE_MOD_TAP_INTERRUPT

#undef RGBLED_NUM
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLED_NUM 10
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
