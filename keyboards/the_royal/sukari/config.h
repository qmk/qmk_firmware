#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4b4b
#define PRODUCT_ID      0x1001
#define DEVICE_VER      0x0001
#define MANUFACTURER    "the-royal"
#define PRODUCT         Sukari
#define DESCRIPTION     'A "True Gasket", 60%, Ortholinear Keyboard'

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

// Matrix Pin-Out
#define MATRIX_ROW_PINS { B4, B5, B6, B7, B0 }
#define MATRIX_COL_PINS { B1, B2, C7, C6, C5, C4, D6, C2, D0, D1, D5, D2 }
#define UNUSED_PINS

// Rear DIP Switch Pin-Out
#define DIP_SWITCH_PINS { D3, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// RGB Indicator and Underglow
#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN D4
    #define RGBLED_NUM 3    // Number of LEDs
// If expanding with pin-out
// #define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_HUE_STEP 6
// #define RGBLIGHT_SAT_STEP 4
// #define RGBLIGHT_VAL_STEP 8
#endif
