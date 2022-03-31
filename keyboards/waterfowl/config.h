#pragma once
#include "config_common.h"


/* USB Device properties */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x9CE3
#define DEVICE_VER      0x0001
#define MANUFACTURER    CyanDuck
#define PRODUCT         Waterfowl

/* Key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// Wiring
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1 }

// COL2ROW, ROW2COL
#define DIODE_DIRECTION COL2ROW

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

// Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.

#define SOFT_SERIAL_PIN D2
#define OLED_DISPLAY_128X64
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_USB_DETECT

// Encoders
#define ENCODERS_PAD_A { B4, B3 }
#define ENCODERS_PAD_B { B5, B2 }
#define ENCODER_RESOLUTIONS { 4, 2 }

// Tapping term
#define TAPPING_TERM 200