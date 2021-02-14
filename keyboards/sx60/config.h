#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5154 // "QT"
#define PRODUCT_ID      0x0010
#define DEVICE_VER      0x0001
#define MANUFACTURER    Quantrik
#define PRODUCT         SX60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
#define ATMEGA_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B2, B3, C6, B6 }
#define MATRIX_COL_PINS { F6, B5, B4, D7, D6, D5, D3, D2 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* indicator LEDs */
#define LED_NUM_LOCK_PIN F5
#define LED_CAPS_LOCK_PIN F4
#define LED_SCROLL_LOCK_PIN F1

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
