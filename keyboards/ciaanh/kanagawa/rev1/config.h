#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xC1E0
#define PRODUCT_ID 0x0010
#define DEVICE_VER 0x0001
#define MANUFACTURER Ciaanh
#define PRODUCT Kanagawa
#define DESCRIPTION 75 with features

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B2, B3, B1, F7, F6, F5 }
#define MATRIX_COL_PINS { B6, F0, F1, C7, D5, B7, B5, B4, E6, D7, C6, D4, D2, D3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef OLED_ENABLE
#   define OLED_DISPLAY_128X64
#   define OLED_FONT_H "lib/oledfont.c"
#   define OLED_FONT_END 255
// #   define OLED_DISPLAY_ADDRESS 0x78
#endif

/* encoder support */
#define ENCODERS_PAD_A \
    { B0 }
#define ENCODERS_PAD_B \
    { F4 }
#define ENCODERS_PAD_A_RIGHT \
    { F4 }
#define ENCODERS_PAD_B_RIGHT \
    { B0 }
#define ENCODER_RESOLUTION 2

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE
