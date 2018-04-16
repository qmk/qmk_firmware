#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#undef RGB_DI_PIN
#undef RGBLED_NUM
#define RGB_DI_PIN D2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#endif