#ifndef CONFIG_H
#define CONFIG_H
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4A48
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    jsor-hpoli
#define PRODUCT         "denial75"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, F6, F5, F4, F1, F0 }
#define MATRIX_COL_PINS { F7, C7, C6, B5, B4, D7, D6, D4, E6, B1, B2, B3, B7, D0, D1, D3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Caps Lock Definition */
#define LED_CAPS_LOCK_PIN B6
#define LED_PIN_ON_STATE 0



/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* RGB Definitions */

#define RGB_DI_PIN D2
#define RGBLED_NUM 84
#define RGBLIGHT_MAX_LAYERS 32
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_LIMIT_VAL 200

#endif
