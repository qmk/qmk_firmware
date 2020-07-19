#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0xADD0
#define DEVICE_VER 0x0001
#define MANUFACTURER akegata denki 
#define PRODUCT device one mechanical keyboard 

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B1, B0, A9, A8, A0 }
#define MATRIX_COL_PINS { A2, A3, A4, A5, A6, A7, A1, A10, A15, B3, B4, B5, B6, B7, B8}

#define DIODE_DIRECTION COL2ROW
