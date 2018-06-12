#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"
#define RGB_DI_PIN F6
#define RGBLED_NUM 10
#define RGBLIGHT_ANIMATIONS
#ifdef BACKLIGHT_LEVELS
#undef BACKLIGHT_LEVELS
#endif
#define BACKLIGHT_LEVELS 3

#endif
