#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* bootmagic salt key */
#define BOOTMAGIC_KEY_SALT              KC_ESC

/* skip bootmagic and eeconfig */
#define BOOTMAGIC_KEY_SKIP              KC_SPACE

#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN B5
#define RGBSPS_NUM 57

#endif
