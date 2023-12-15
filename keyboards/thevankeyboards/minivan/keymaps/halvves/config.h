#pragma once

#define TAPPING_TERM 505
#define PERMISSIVE_HOLD
#define RETRO_TAPPING

// smooth mousekeys (copied from the ergo ez config)
#ifdef MOUSEKEY_ENABLE
  #define MOUSEKEY_INTERVAL 16
  #define MOUSEKEY_DELAY 0
  #define MOUSEKEY_TIME_TO_MAX 60
  #define MOUSEKEY_MAX_SPEED 7
  #define MOUSEKEY_WHEEL_DELAY 0
#endif

#ifdef RGBLIGHT_ENABLE
  #define WS2812_DI_PIN D0
  #define RGBLED_NUM 3
  #define RGBLIGHT_EFFECT_BREATHING
#endif
