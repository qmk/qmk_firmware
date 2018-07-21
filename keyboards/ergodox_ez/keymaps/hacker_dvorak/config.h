/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#ifndef CONFIG_HACKER_DVORAK_H
#define CONFIG_HACKER_DVORAK_H

#include "../../config.h"

// Keyboard Settings
#undef TAPPING_TERM
#define TAPPING_TERM 1000

#undef DEBOUNCE
#define DEBOUNCE 10

#undef ONESHOT_TAP_TOGGLE
#define ONESHOT_TAP_TOGGLE 1

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 1000

#undef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD

#undef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT

#undef NO_DEBUG
#define NO_DEBUG

#undef NO_PRINT
#define NO_PRINT

#undef FORCE_NKRO
#define FORCE_NKRO

// RGB Lights
#undef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 24

#undef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 24

#undef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 24

#undef RGBLIGHT_BRI_STEP
#define RGBLIGHT_BRI_STEP 24

#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 255

#undef RGBLIGHT_SLEEP
#define RGBLIGHT_SLEEP

// Mouse
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 10

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 15

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 15

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 150

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 15

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 150

#endif
