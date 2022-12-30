#pragma once

#define MASTER_LEFT

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_LAYERS
  #undef RGBLED_NUM
  #define RGBLED_NUM 54
  #undef RGBLED_SPLIT
  #define RGBLED_SPLIT {27, 27}
  #define RGBLIGHT_LIMIT_VAL 120
  #define RGBLIGHT_HUE_STEP 10
  #define RGBLIGHT_SAT_STEP 17
  #define RGBLIGHT_VAL_STEP 17
#endif
