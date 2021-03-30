#ifndef CONFIG_KEYMAP_H
#define CONFIG_KEYMAP_H

#include "../../config.h"

#define USE_SERIAL
#define EE_HANDS

// LED strip stuff
#ifdef RGBLIGHT_ENABLE

// Who thought it was a good idea to predefine these in the rev2/config.h ???
#ifdef RGBLED_NUM
#undef RGBLED_NUM
#endif
#define RGBLED_NUM 12

#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 20
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 6
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 2000
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#endif

#endif
