/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#pragma once


/* Keyboard Settings */
#undef  TAPPING_TERM
#define TAPPING_TERM 150

#undef  DEBOUNCE
#define DEBOUNCE 10

#undef  IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT

#undef  FORCE_NKRO
#define FORCE_NKRO

/* This isn't defined by default, so there is no need to undefine it first. */
#define LEADER_TIMEOUT 500
#define PERMISSIVE_HOLD
#define QMK_KEYS_PER_SCAN 4


// RGB Lights
#undef  RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 24

#undef  RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 24

#undef  RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 24

#undef  RGBLIGHT_BRI_STEP
#define RGBLIGHT_BRI_STEP 24

#undef  RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 255

/* This isn't defined by default, so there is no need to undefine it first. */
#define RGBLIGHT_SLEEP


// Mouse
#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 10

#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 15

#undef  MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 15

#undef  MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 150

#undef  MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 15

#undef  MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 150


/* This is defined only if CONSOLE_ENABLE is set to "yes" */
// #undef  NO_DEBUG
// #define NO_DEBUG

// #undef  NO_PRINT
// #define NO_PRINT

/* For COMBO only*/
// #define COMBO_COUNT 1
// #define COMBO_TERM 200

/* For tap toggle */
// #define TAPPING_TOGGLE 2
// #define ONESHOT_TAP_TOGGLE 2
// #define ONESHOT_TIMEOUT 300

