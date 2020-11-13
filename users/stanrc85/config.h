#pragma once

#define TAPPING_TERM 250
#define RETRO_TAPPING

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_SLEEP
#endif

#ifdef SNEAKBOX
  #define INDICATOR_PIN_0 D7
  #define INDICATOR_PIN_1 D6
  #define INDICATOR_PIN_2 D4 
#endif
