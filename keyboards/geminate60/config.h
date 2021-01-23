#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x7764
#define PRODUCT_ID 0x676d
#define DEVICE_VER 0x0001
#define MANUFACTURER Weirdo
#define PRODUCT Geminate60


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A9, A10, B10, B11, B15}
#define MATRIX_COL_PINS { A8, B14, B13, B12, B1, B0, A7 , A1 , A15, B3, B4, B5, B6, B7, B8}
#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5



#define RGB_DI_PIN A6
#define RGBLED_NUM 1
#define RGBLIGHT_LED_MAP {0}
//#define RGBLIGHT_DISABLE_KEYCODES




/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#ifdef CONSOLE_ENABLE
//#define DEBUG_MATRIX_SCAN_RATE
#endif
#endif
