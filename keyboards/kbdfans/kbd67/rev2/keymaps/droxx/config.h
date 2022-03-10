#pragma once

/* USB Device descriptor parameter */
#undef VENDOR_ID
#undef MANUFACTURER
#undef PRODUCT

#define VENDOR_ID       0xAF88
#define PRODUCT_ID      0x6067
#define DEVICE_VER      0x0002
#define MANUFACTURER    Droxx-FurFuzz
#define PRODUCT         Carbon v2 4rk

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B7, D0, F0, F1, F4 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, D1, D2, D3, D6, D7, B4, B6, C6, C7, F7, F6, F5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#undef RGBLIGHT_LIMIT_VAL

#define RGBLIGHT_LIMIT_VAL 255

/* Debouncing reduces chatter */
#define DEBOUNCE 5

/* force N key rollover even on startup regardless of EEPROM setting */
#define FORCE_NKRO

/* USB polling rate */
#define USB_POLLING_INTERVAL_MS 1

/* turn off RGB when computer sleeps */
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif