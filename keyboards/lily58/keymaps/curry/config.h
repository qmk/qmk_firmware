#pragma once

#define EE_HANDS

#define OLED_DISABLE_TIMEOUT
#define TAPPING_TERM_PER_KEY

#if defined(RGBLIGHT_ENABLE)
#    undef RGBLED_NUM
#    define RGBLED_NUM 27

#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 120
#endif

//  comment out unnecessary layouts
#define ENABLE_QWERTY
#define ENABLE_COLEMAK
#define ENABLE_DVORAK
