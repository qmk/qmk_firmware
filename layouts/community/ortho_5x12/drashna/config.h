#pragma once


/* ws2812 RGB LED */
#if defined(KEYBOARD_fractal)
  #define RGB_DI_PIN D2
  #undef RGBLED_NUM
  #define RGBLIGHT_ANIMATIONS
  #define RGBLED_NUM 29     // Number of LEDs
  #undef RGBLIGHT_HUE_STEP
  #define RGBLIGHT_HUE_STEP 8
  #undef RGBLIGHT_SAT_STEP
  #define RGBLIGHT_SAT_STEP 8
  #undef RGBLIGHT_VAL_STEP
  #define RGBLIGHT_VAL_STEP 8
#endif
