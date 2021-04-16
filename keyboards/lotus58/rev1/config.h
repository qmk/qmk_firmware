#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFC32
#define PRODUCT_ID      0x0287
#define DEVICE_VER      0x0011
#define MANUFACTURER    MarkusKnutsson
#define PRODUCT         Lotus58

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { B1, B2, B3, B6, F7, F6 }
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 175
#define TAPPING_TOGGLE 2
//#define TAP_CODE_DELAY 10
#define DEBOUNCE 5

/* encoder support */
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTION 2

/* communication */
#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
#define SOFT_SERIAL_PIN D2
#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSPORT_MIRROR

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

#define SPLIT_HAND_PIN B5
#define MASTER_RIGHT

/* RGB */
#define RGB_DI_PIN D3
#define RGBLED_SPLIT { 35, 35 }