#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1337
#define DEVICE_VER      0x0001
#define MANUFACTURER    g Heavy Industries
#define PRODUCT         Butter Stick
#define DESCRIPTION     Its a stick of butter
#define VERSION 		"Paula Deen"

#define DEBOUNCE 5
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 10
#define MATRIX_ROW_PINS { F4, F5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5, B6, B7, C6, C7}
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL
