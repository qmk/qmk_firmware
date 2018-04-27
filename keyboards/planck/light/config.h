#ifndef LIGHT_CONFIG_H
#define LIGHT_CONFIG_H

#include "config_common.h"

#undef PRODUCT
#define PRODUCT Planck Light
#undef PRODUCT_ID
#define PRODUCT_ID 0x6065
#define DEVICE_VER 0x0001

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { B0, E7, F0, F1 }
#define MATRIX_COL_PINS { E6, E3, E4, D3, D4, D5, C0, A7, A6, E1, E0, D7 }

#define C6_AUDIO
#define B5_AUDIO

#undef BACKLIGHT_PIN

#define BACKLIGHT_PIN A5

#define NO_USB_STARTUP_CHECK


#endif