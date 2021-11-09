#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x7363  // Stream Cheap
#define PRODUCT_ID 0x1214
#define DEVICE_VER 0x0001
#define MANUFACTURER Stream Cheap
#define PRODUCT 2x4

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* define direct pins used */
//Luigi311
//#define DIRECT_PINS { { B4, E6, D4, D0}, { B5, D7, C6, D1} }
//Darklegacy
//#define DIRECT_PINS { { B4, D4, D7, D1}, { B5, C6, D0, E6} }
//Vancurls Craigerbomb Scuhzy
//#define DIRECT_PINS { { D7, E6, B3, B1}, { B5, B4, B2, B6} }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
