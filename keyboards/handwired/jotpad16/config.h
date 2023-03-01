#pragma once


/* pro_micro pin-out */
#define MATRIX_ROW_PINS { B6, B2, D2, D3 }
#define MATRIX_COL_PINS { E6, D7, B3, B1 }

/* leds */
#define JOTPAD16_LEDS
#define JOTPAD16_LED1 B5
#define JOTPAD16_LED2 B4

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
