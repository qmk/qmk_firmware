#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#define AUDIO_INIT_DELAY

#include "../../config.h"

#define TAPPING_TERM 165
#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
//#define BACKLIGHT_ENABLE
#endif
