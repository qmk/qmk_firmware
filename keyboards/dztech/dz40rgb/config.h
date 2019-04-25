#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1220
#define DEVICE_VER      0x0001
#define MANUFACTURER    DZTECH
#define PRODUCT         DZ40RGB
#define DESCRIPTION     DZ40 ARM RGB keyboard
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { B13, B12, A2, A1 }
#define MATRIX_COL_PINS {A6, A7, B0, B1, C15, C14, C13, B9, B8, A8, B14, B15 }

/* #define UNUSED_PINS {A0,A1,A2, A3,A4,A9,A10,C15,A13,A14,B2}*/

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 3
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.

#define DRIVER_COUNT 2
