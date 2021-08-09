/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef TAPPING_TERM
#define TAPPING_TERM 170

#define PERMISSIVE_HOLD

#define USB_SUSPEND_WAKEUP_DELAY 0

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#undef MK_W_OFFSET_UNMOD
#define MK_W_OFFSET_UNMOD 15
#undef MK_W_INTERVAL_UNMOD
#define MK_W_INTERVAL_UNMOD 80