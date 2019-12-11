#pragma once

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 12

#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 3
#endif  // RGBLIGHT_ENABLE

#undef PRODUCT
#define PRODUCT DrashnaDox - Hacked ErgoDox EZ Shine

#undef DEBOUNCE
#define DEBOUNCE 30

#define TAPPING_TERM_PER_KEY

#define ERGODOX_LED_30
