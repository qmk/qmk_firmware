#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 18
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
