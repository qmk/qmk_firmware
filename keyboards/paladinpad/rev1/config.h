#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

#include "config_common.h"

#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { C7, B6, B4, D7, D6 }
#define MATRIX_COL_PINS { D4, D5, D3, B7 }
#define UNUSED_PINS

#define RGB_DI_PIN D0

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 12
#endif

#endif
