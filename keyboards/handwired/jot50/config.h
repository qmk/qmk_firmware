#pragma once


/* pro_micro pin-out */
#define MATRIX_ROW_PINS { D7, E6, B4, B6, B2 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, D3, D2, D1, D0, D4, C6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
