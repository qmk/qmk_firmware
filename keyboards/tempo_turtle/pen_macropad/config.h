#pragma once

#include "config_common.h"

/*usb descriptor setup*/

#define VENDOR_ID 0x7474
#define PRODUCT_ID 0x706d
#define DEVICE_VER 0x0000
#define MANUFACTURER Turtle Tech
#define PRODUCT Pen Macropad
#define DESCRIPTION "A Macropad with Pen Support"

/* keeb stuff */

#define MATRIX_ROWS 6
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS {C7, B5, B4, B6, B2, E6}
#define MATRIX_COL_PINS {D1, D0, F5, F4}
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5