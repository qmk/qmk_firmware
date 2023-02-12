#pragma once


/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* define direct pins used */
#define DIRECT_PINS { { D1,C6,B4}, { D0,D4,D7} }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
