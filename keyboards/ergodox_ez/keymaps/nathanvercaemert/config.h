/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR

// max layer limit
#undef LAYER_STATE_16BIT
#define LAYER_STATE_32BIT

#undef TAPPING_TERM
#define TAPPING_TERM 175

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 20

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 14

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 30

#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 50

#undef MK_KINETIC_SPEED
#undef MK_COMBINED
#define MK_COMBINED

// Trying to save space

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Need to uncomment for debug

#ifndef NO_DEBUG
#define NO_DEBUG
#endif
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif
