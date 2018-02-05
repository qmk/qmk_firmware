#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* bootmagic salt key */
#define BOOTMAGIC_KEY_SALT              KC_ESC

/* skip bootmagic and eeconfig */
#define BOOTMAGIC_KEY_SKIP              KC_SPACE

/* ws2812 RGB LED */
#define RGB_DI_PIN D5
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 13     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#endif
