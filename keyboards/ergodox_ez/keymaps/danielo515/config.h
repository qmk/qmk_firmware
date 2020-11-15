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

#undef DEBOUNCE
#define DEBOUNCE 45
// Memory saving
#ifdef CONSOLE_ENABLE
#    define NO_DEBUG
#    define NO_PRINT
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#undef RGBLIGHT_ANIMATIONS
