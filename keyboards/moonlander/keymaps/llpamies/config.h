/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define RGB_DISABLE_TIMEOUT 300000
#define USB_SUSPEND_WAKEUP_DELAY 0
#define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT 193
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC
#define FIRMWARE_VERSION u8"personal"
#define RGB_MATRIX_STARTUP_SPD 60
#define COMBO_COUNT 13
#define COMBO_TERM 30

// Hold and tap config.
#define TAPPING_TERM 200
//#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
