#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { C3, C2, C1, C0, E1 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D5, D7, E0, C7, C6, C5, C4, F0, F1, F2, F3, F4, F5, F6, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* force n-key rollover*/
#define FORCE_NKRO

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
