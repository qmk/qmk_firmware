#pragma once

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0002

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS  7 

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
#define MATRIX_ROW_PINS { D7, E0, E1, C0, C6, F6, D4, D2, D3, D0, B7, D1, E6, B4, B2 }
#define MATRIX_COL_PINS { E7, F0, F7, B1, B3, B0, D5 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN C5
#define LED_CAPS_LOCK_PIN C1
#define LED_SCROLL_LOCK_PIN C4
#define LED_COMPOSE_PIN C3
#define LED_PIN_ON_STATE 0

/* Well-worn Cherry MX key switches can bounce for up to 20ms, despite the
 * Cherry data sheet specifying 5ms. Because we use the sym_eager_pk debounce
 * algorithm, this debounce latency only affects key releases (not key
 * presses). */
#undef DEBOUNCE
#define DEBOUNCE 20

#define IGNORE_MOD_TAP_INTERRUPT

// The Teensy 2++ consumes about 60 mA of current at its full speed of 16 MHz as
// per https://www.pjrc.com/teensy/low_power.html
#define USB_MAX_POWER_CONSUMPTION 100
