#pragma once


// key matrix pins
#define MATRIX_ROW_PINS { B2, B1, B0, C7, F6, F7, B3, D1, D2, D7, B6, C6 }
#define MATRIX_COL_PINS { E6, D5, B7, D0, F5, D3, B4, B5, D4, D6 }

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE
