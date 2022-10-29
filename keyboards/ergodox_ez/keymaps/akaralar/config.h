/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
// #define ORYX_CONFIGURATOR
#define TAPPING_FORCE_HOLD
// #define PERMISSIVE_HOLD  

#undef RGB_DISABLE_TIMEOUT
#define RGB_DISABLE_TIMEOUT 300000

#define USB_SUSPEND_WAKEUP_DELAY 0
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#define CAPS_LOCK_STATUS
#define RGB_MATRIX_STARTUP_SPD 60

// Activate Caps Word by pressing both shift keys
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Turn off Caps Word after 3 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 2000  