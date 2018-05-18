#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define MIDI_BASIC

#define USE_SERIAL

#define EE_HANDS

#ifdef KEYBOARD_planck
  #undef RGBLED_NUM
  #define RGBLED_NUM 10
  #define RGB_DI_PIN D1
#endif
#ifdef KEYBOARD_levinson
  #undef RGBLED_NUM
  #define RGBLED_NUM_12
#endif
#ifdef KEYBOARD_lets_split
  #undef RGBLED_NUB
  #define RGBLED_NUM_8
#endif

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 8

#endif
