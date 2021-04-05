#pragma once
#include "config_common.h"
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1225
#define DEVICE_VER      0x0001
#define MANUFACTURER    X-BOWS
#define PRODUCT         KNIGHT

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 15

// wiring of each half
#define MATRIX_ROW_PINS { D2, E6, E2, F7, F6, F5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, F4, F1, C6, B6, B5, B4, D7, D6, D4, D5, D3}
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define LED_NUM_LOCK_PIN D1
#define LED_CAPS_LOCK_PIN C7
#define LED_PIN_ON_STATE 0

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
#endif
/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define SPLIT_HAND_PIN F0
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

