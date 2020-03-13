#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define DEVICE_VER      0x0200
#define MANUFACTURER    mehkee
#define PRODUCT         96kee

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS
/* key combination for command */
