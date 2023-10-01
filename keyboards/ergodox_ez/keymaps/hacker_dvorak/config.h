/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#pragma once


#undef  TAPPING_TERM
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY

#undef  DEBOUNCE
#define DEBOUNCE 15


#define RGB_DISABLE_WHEN_USB_SUSPENDED

#undef  FORCE_NKRO
#define FORCE_NKRO

#undef  TAPPING_TOGGLE
#define TAPPING_TOGGLE 5

#define LEADER_TIMEOUT 1000
#define PERMISSIVE_HOLD
#define DANCING_TERM 175

#define ONESHOT_TAP_TOGGLE 5

#undef  ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 5000

#define COMBO_TERM 200

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


#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 10

#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 15

#undef  MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 20

#undef  MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 200

#undef  MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 20

#undef  MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 200


// #undef  NO_DEBUG
// #define NO_DEBUG

// #undef  NO_PRINT
// #define NO_PRINT

// #define RETRO_TAPPING
// #define QUICK_TAP_TERM 0

// #define AUTO_SHIFT_TIMEOUT 150
// #define NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_NUMERIC
// #define NO_AUTO_SHIFT_ALPHA

// #define EXTRA_LONG_COMBOS
// #define EXTRA_EXTRA_LONG_COMBOS
// #define COMBO_ALLOW_ACTION_KEYS

// #define RGBLIGHT_SLEEP
