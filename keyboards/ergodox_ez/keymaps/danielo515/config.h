/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#pragma once 

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200

#define ONESHOT_TAP_TOGGLE 3

#define RGBLIGHT_SLEEP

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 50

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60
// Timeout settings for leader key
#undef  LEADER_TIMEOUT
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING

// Memory saving
#undef NO_DEBUG
#define NO_DEBUG
#undef NO_PRINT
#define NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#undef RGBLIGHT_ANIMATIONS
