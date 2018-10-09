#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEEB
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Fox-Lab
#define PRODUCT         Orange75
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { E6,F0, F1, F4, F5, F6, F7, C7, C6, B6, B4, D7, D4, D5, D6 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, B7, B3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B5
#define BACKLIGHT_LEVELS 3


/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
