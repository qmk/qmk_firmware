#pragma once

/* matrix pins */
#define MATRIX_ROW_PINS { B4, E2, F4, F7, F1, F6, C6, F5, D7, C7 }
#define MATRIX_COL_PINS { E6, B0, B1, B2, B3, F0, D0, D5 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
