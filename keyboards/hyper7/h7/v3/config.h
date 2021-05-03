#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    yiancar
#define PRODUCT         hyper7 v3.0

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 28

/* key matrix pins */
/*
 * v2.0 #define MATRIX_ROW_PINS { F1, F0, E4, E5, D4, D5, D6, D7 }
 * v3.0 #define MATRIX_ROW_PINS { F1, F0, E6, E5, D4, D5, D6, D7 }
 */
#define MATRIX_ROW_PINS { F1, F0, E6, E5, D4, D5, D6, D7 }
#define MATRIX_COL_PINS { F2, F3, F4, F5, F6, F7, A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, C1, C0, E1, E0, D3, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 6
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

// see: https://docs.qmk.fm/#/feature_leader_key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
