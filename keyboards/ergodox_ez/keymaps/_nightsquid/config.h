/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef DEBOUNCE
#define DEBOUNCE 77

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 14 

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED  7

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 49

#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 3

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 4 

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 77

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2

#define MIDI_ADVANCED