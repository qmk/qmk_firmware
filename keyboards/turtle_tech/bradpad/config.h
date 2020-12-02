#pragma once

#include "config_common.h"

/*usb descriptor setup*/

#define VENDOR_ID 0x7474
#define PRODUCT_ID 0x706d
#define DEVICE_VER 0x0000
#define MANUFACTURER Turtle Tech
#define PRODUCT BradPad
#define DESCRIPTION "A Portable Music Production Pad"

/* keeb stuff */

#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS {B7, D5, C7, D2, D3}
#define MATRIX_COL_PINS {D7, E6, B4, F1}
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5