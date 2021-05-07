#pragma once
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#undef TAPPING_TERM
#define TAPPING_TERM 200

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

// Underglow

#undef RGBLED_NUM
#define RGBLED_NUM 10    // Number of LEDs
#define RGBLED_SPLIT { 5, 5 }
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP

#define BACKLIGHT_PIN B7