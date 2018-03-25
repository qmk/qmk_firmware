#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H


#ifdef RGBLIGHT_ENABLE
#undef RGBLIGHT_SAT_STEP 
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 7
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 7
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 175
#undef PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
#define ONESHOT_TAP_TOGGLE 2

#undef PRODUCT
#define PRODUCT         DrashnaDox - Hacked ErgoDox EZ Shine

#endif
