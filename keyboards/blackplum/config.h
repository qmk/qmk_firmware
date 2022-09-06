#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5058 // "PX"
#define PRODUCT_ID      0x4250 // "BP"
#define DEVICE_VER      0x1001
#define MANUFACTURER    Pixlup
#define PRODUCT         Blackplum Keeb

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { C6, B6, B4, B5, D6, D7, D5, D3, D4 }
#define MATRIX_COL_PINS { D0, D1, D2, F7, F6, F5, F4, F1 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* ws2812 RGB LED */
#define RGB_DI_PIN C7
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16    // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_SLEEP
