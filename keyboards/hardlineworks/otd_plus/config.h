#pragma once


#define MATRIX_ROW_PINS { D2, D4, D1, E6, F5, C6, B6, F6, F0, D0, D6, D3 }
#define MATRIX_COL_PINS { B3, B2, B1, B7, B0, F1, D7, F7, C7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
