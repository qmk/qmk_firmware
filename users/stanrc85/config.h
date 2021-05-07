#pragma once

#define TAPPING_TERM 250
#define RETRO_TAPPING
#define FORCE_NKRO

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_SLEEP
#endif

#ifdef KEYBOARD_sneakbox_aliceclone
  #define INDICATOR_PIN_0 D7
  #define INDICATOR_PIN_1 D6
  #define INDICATOR_PIN_2 D4 
#endif

#ifdef KEYBOARD_boardsource_the_mark
  #define RGB_MATRIX_KEYPRESSES
#endif