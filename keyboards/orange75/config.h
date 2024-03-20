#pragma once

/* key matrix pins */
#define MATRIX_ROW_PINS { E6,F0, F1, F4, F5, F6, F7, C7, C6, B6, B4, D7, D4, D5, D6 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, B7, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
