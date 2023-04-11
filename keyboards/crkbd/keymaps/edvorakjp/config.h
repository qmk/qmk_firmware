#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SWAP_SCLN

// #define QUICK_TAP_TERM 0
#define TAPPING_TERM 300
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLED_NUM 27
#    define RGBLIGHT_LIMIT_VAL 100
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif  // RGBLIGHT_ENABLE

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
