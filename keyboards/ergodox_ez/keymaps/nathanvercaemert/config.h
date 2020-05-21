/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
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

// /* Temporarily defining a tapping term that is ridiculous to see if i can tell if lt is working. */
// #undef TAPPING_TERM
// #define TAPPING_TERM 499

/* Turning permissive hold and ignore mod tap interrupt off in order to test the tapping term. */
#undef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD
#undef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT
