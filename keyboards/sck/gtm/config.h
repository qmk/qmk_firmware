#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { C4, C5, D1 }
#define MATRIX_COL_PINS { B4, B5, B6, B7, C7, D0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B0
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
#endif
