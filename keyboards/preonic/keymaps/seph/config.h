#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// Number of backlight levels
#undef  BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 8

/* ws2812 RGB LED */
#undef RGB_DI_PIN
#define RGB_DI_PIN B3
#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 11     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17


#endif
