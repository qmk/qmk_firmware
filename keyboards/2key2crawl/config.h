#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { C4, C5 }
#define MATRIX_COL_PINS { B3, B4, B5, B6, B7, C7, B2 }
#define UNUSED_PINS


#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D1 }
#define ENCODER_RESOLUTION 1

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN C6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 3
#endif
