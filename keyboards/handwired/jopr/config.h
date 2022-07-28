#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 11

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D6, D2, D4, D3, D5, D7, C6, B6, F5 }
#define MATRIX_COL_PINS { B3, B2, B1, B0, F7, E6, F6, B5, C7, B4, D1 }
#define UNUSED_PINS { B7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT
#define TAPPING_TOGGLE 3

/*#define RGB_DI_PIN F4*/
#ifdef RGB_DI_PIN
/*#define RGBLIGHT_ANIMATIONS*/
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 1
#define RGBLIGHT_SAT_STEP 1
#define RGBLIGHT_VAL_STEP 1
#endif
