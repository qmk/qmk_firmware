#ifndef CONFIG_USER_H
  #define CONFIG_USER_H
  #include "../../config.h"
  #define PERMISSIVE_HOLD
  #ifdef RGBLIGHT_ENABLE
    // This is the only effect I care about for this board
    #define RGBLIGHT_EFFECT_BREATHING
  #endif
#endif
