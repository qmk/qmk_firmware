#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D6, D2, D4, D3, D5, D7, C6, B6, F5 }
#define MATRIX_COL_PINS { B3, B2, B1, B0, F7, E6, F6, B5, C7, B4, D1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT
#define TAPPING_TOGGLE 3

/*#define RGB_DI_PIN F4*/
#ifdef RGB_DI_PIN
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 1
#define RGBLIGHT_SAT_STEP 1
#define RGBLIGHT_VAL_STEP 1
#endif
