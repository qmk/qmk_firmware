#ifndef KEYMAP_IRIS_PVINIS_CONFIG_H
#define KEYMAP_IRIS_PVINIS_CONFIG_H

#include "config_common.h"


#ifdef PRODUCT
#undef PRODUCT
#define PRODUCT Iris Keyboard - pvinis
#endif // PRODUCT


// Use I2C or Serial, not both
#define USE_SERIAL
// #define USE_I2C


// Select hand configuration
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS


// choose pin to use for audio. c6 is the one iris uses.
#ifdef AUDIO_ENABLE
#define C6_AUDIO
#endif // AUDIO_ENABLE


#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8


#endif // !KEYMAP_IRIS_PVINIS_CONFIG_H
