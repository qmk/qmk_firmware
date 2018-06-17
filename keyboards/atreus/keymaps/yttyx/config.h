#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

// Mouse speed

#define MOUSEKEY_INTERVAL           10
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        1
#define MOUSEKEY_MAX_SPEED          10

#define MOUSEKEY_WHEEL_DELAY        0
#define MOUSEKEY_WHEEL_DELTA        1
#define MOUSEKEY_WHEEL_MAX_SPEED    6
#define MOUSEKEY_WHEEL_TIME_TO_MAX  1

// USB Device descriptor parameters
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Technomancy
#define PRODUCT         Atreus
#define DESCRIPTION     QMK keyboard firmware for Atreus

// key matrix size
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

// Change this to how you wired your keyboard
// COLS: Left to right, ROWS: Top to bottom
#if defined(ATREUS_ASTAR)
#   define MATRIX_ROW_PINS { D0, D1, D3, D2 }
#if defined(PCBDOWN)
#   define MATRIX_COL_PINS { B7, D6, F7, F6, B6, D4, E6, B4, B5, C6, D7 }
#else
#   define MATRIX_COL_PINS { D7, C6, B5, B4, E6, D4, B6, F6, F7, D6, B7 }
#endif
#   define UNUSED_PINS
#elif defined(ATREUS_TEENSY2)
#   define MATRIX_ROW_PINS { D0, D1, D2, D3 }
#   define MATRIX_COL_PINS { F6, F5, F4, B7, B6, B5, B4, B3, B2, B1, B0 }
#   define UNUSED_PINS
#endif

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCING_DELAY 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// Disable some options to reduce firmware size

// Disable print
#define NO_PRINT

// Disable action features
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
