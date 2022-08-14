#pragma once

#include "config_common.h"

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */

#define DIRECT_PINS { { F4, F5, F6, F7 }, { B1, B3, B2, B6 } }

#define BACKLIGHT_LED_COUNT 8
#undef BACKLIGHT_PIN
#define BACKLIGHT_PINS { D1, D0, D4, C6, D7, E6, B4, B5 }
#define BACKLIGHT_LEVELS 8

// ws2812 options
#define RGB_DI_PIN D2 // pin the DI on the ws2812 is hooked-up to
#define RGBLED_NUM 8 // number of LEDs
#define RGBLIGHT_ANIMATIONS
