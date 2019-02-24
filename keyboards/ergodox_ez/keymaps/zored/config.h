/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#undef DEBOUNCE
#define DEBOUNCE 10

#undef TAPPING_TERM
#define TAPPING_TERM 124

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 10

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 55

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_leader_key.md
#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING