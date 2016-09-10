#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define LEADER_TIMEOUT 300
#define BACKLIGHT_BREATHING


/* ws2812 RGB LED */
#define RGB_DI_PIN B1
#define RGBLIGHT_TIMER
#define RGBLED_NUM 8     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#endif
