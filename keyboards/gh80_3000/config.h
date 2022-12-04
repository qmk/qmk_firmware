#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F1, F0, F5, F6, F7, D4, D5, D3, D2, D0 }
#define MATRIX_COL_PINS { C7, C6, B4, D7, B3, B2, B0, E6, B1, D1, D6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
