#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x1209
#define PRODUCT_ID 0x2201
#define DEVICE_VER 0x0001
#define MANUFACTURER Dygma
#define PRODUCT Raise

/* key matrix size */
// rows are doubled for split
#define MATRIX_ROWS 10
#define MATRIX_COLS 8
/* The scanners already debounce for us */
#define DEBOUNCE 0

#define DRIVER_LED_TOTAL 132
