#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5058 // "PX"
#define PRODUCT_ID      0x5445 // "TE"
#define DEVICE_VER      0x1001
#define MANUFACTURER    Pixlup
#define PRODUCT         TENKI
#define DESCRIPTION     Customizable Mechanical Numpad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B4, F6, B6, B2 }
#define MATRIX_COL_PINS { F4, F5, D4, D0 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* ws2812 RGB LED */
#define RGB_DI_PIN D1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 3   // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_SLEEP
