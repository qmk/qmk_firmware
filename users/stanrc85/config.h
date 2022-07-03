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

#if defined(KEYBOARD_mechlovin_adelais_standard_led_arm_rev4_stm32f303) || defined(KEYBOARD_mechlovin_adelais_standard_led_arm_rev4_apm32f103)
  #define INDICATOR_PIN_0 B2
  #define INDICATOR_PIN_1 C15
  #define INDICATOR_PIN_2 B9
#endif

#ifdef KEYBOARD_boardsource_the_mark
  #define RGB_MATRIX_KEYPRESSES
#endif

#ifdef KEYBOARD_jacky_studio_bear_65
  #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define ENABLE_RGB_MATRIX_MULTISPLASH
  #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#endif

#ifdef KEYBOARD_nasu
  #define INDICATOR_PIN_0 B1
  #define INDICATOR_PIN_1 B0
  #define INDICATOR_PIN_2 A7
#endif
