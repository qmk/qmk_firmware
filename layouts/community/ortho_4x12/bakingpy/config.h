#pragma once

#define USE_I2C

/* Select hand configuration */
//#define MASTER_RIGHT

#define TAPPING_TERM 150

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#ifdef AUDIO_ENABLE
#define C6_AUDIO
#endif
