#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBF00
#define PRODUCT_ID      0xBF22
#define DEVICE_VER      0x0001
#define MANUFACTURER    Daji
#define PRODUCT         Seis Cinco
#define DESCRIPTION     65 layout keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
*/
#define MATRIX_ROW_PINS { B2, B10, B11, A9, A6 }
#define MATRIX_COL_PINS { B1, B0, A7, B14, A8, B15, A0, C15, C14, C13, B5, B4, B3, A15, A10, A14 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* VIA layouts
 * 2 bits = 4 layout options
 */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
