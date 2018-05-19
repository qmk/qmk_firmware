#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define MIDI_BASIC

#define USE_SERIAL

#define EE_HANDS

#undef RGBLED_NUM
#ifdef KEYBOARD_planck_rev5
  #define RGBLED_NUM 10
  #define RGB_DI_PIN D1
#endif
#ifdef KEYBOARD_levinson_rev2
  #define RGBLED_NUM
#endif
#ifdef KEYBOARD_lets_split_rev2
  #define RGBLED_NUM
#endif

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 8

#endif
