#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xEEEE
#define PRODUCT_ID      0x2019
#define DEVICE_VER      0x0002
#define MANUFACTURER    Michael Weber
#define PRODUCT         MisteRDeck

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, E6, D7 }
#define MATRIX_COL_PINS { C6, D4, D0, D1 }
#define UNUSED_PINS

#define TAPPING_TOGGLE 2

#define RGB_DI_PIN B5
#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LAYERS
// #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
#define VIAL_KEYBOARD_UID {0x2B, 0x5F, 0xA7, 0x6F, 0x0B, 0xF9, 0xC8, 0xC0}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }
