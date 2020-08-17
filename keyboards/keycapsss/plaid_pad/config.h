#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x7983
#define PRODUCT_ID 0x7070   //  8-bit ASCII for PP
#define DEVICE_VER 0x0001
#define MANUFACTURER Keycapsss
#define PRODUCT Plaid-Pad
#define DESCRIPTION 4x4 numpad with through hole components

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { C0, C1, C2, C3 }
#define MATRIX_COL_PINS { B0, D7, D6, D5 }
#define UNUSED_PINS     { }

#define ENCODERS_PAD_A { D1, B2, B4, D4 }
#define ENCODERS_PAD_B { D0, B1, B3, B5 }

#define ENCODER_RESOLUTION 4

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define USB_MAX_POWER_CONSUMPTION 100

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
