#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { C6, F7, D7, B1, B4, B2, B5, B6 }
#define MATRIX_COL_PINS { D1, F4, D0, F5, D4, F6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F1
