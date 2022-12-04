#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D3, F5 }
#define MATRIX_COL_PINS { F0, F7, F6, F4, F1, E6, D6, D2, B4, D7, B6, D5 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#define RGB_DI_PIN B1
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
