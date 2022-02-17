#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x6583
#define PRODUCT_ID 0x6080
#define DEVICE_VER 0x0001
#define MANUFACTURER Basic IO Instruments
#define PRODUCT BIOI G60 BLE

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS \
    { E6, B0, F1, F5, F4 }
#define MATRIX_COL_PINS \
    { F6, F7, B3, C7, C6, B6, B5, D5, B4, D7, D6, D4, D1, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#    define BACKLIGHT_LEVELS 8
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN B1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 36
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L
