/*
 * Keybit8 - QMK Firmware Configuration
 * 2x4 Key Matrix with Layer Support
 */

#pragma once

/* USB Device descriptor parameter */
/* USB Device descriptor is defined in info.json */

/* VIA/Remap configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 * Arduino pin numbers:
 *  rowPins[2] = {21, 20}; -> F4, F5
 *  colPins[4] = {4, 5, 6, 7}; -> D4, C6, D7, E6
 */
#define MATRIX_ROW_PINS { F4, F5 }           // Pins 21, 20 (Arduino Pro Micro)
#define MATRIX_COL_PINS { D4, C6, D7, E6 }   // Pins 4, 5, 6, 7 (Arduino Pro Micro)

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* LAYOUT macro is defined in info.json */

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Tapping term for layer toggle keys (200ms default, 50ms was too short) */
#define TAPPING_TERM 200

/* Prevent key repeat when holding LT keys - allows holding without triggering tap */
#define PERMISSIVE_HOLD

/* Combo recognition window (ms) */
#define COMBO_TERM 40

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resync enable */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

/* LED and Speaker pin definitions for Web Game */
/* Arduino Pro Micro pin numbers:
 *  Pin 0 = D3 (PD0)
 *  Pin 1 = D2 (PD1)
 *  Pin 8 = B4 (PB4)
 *  Pin 9 = B5 (PB5)
 *  Pin 10 = B6 (PB6)
 *  Pin 14 = B3 (PB3)
 *  Pin 15 = B2 (PB2)
 *  Pin 16 = B1 (PB1)
 *  Pin 18 = F7 (PF7)
 *  Pin 19 = F6 (PF6)
 */

/* Red LED pins (8 LEDs) */
#define RED_LED_PINS { D2, B4, B1, B2, D3, B5, B3, F7 }
#define RED_LED_COUNT 8

/* Green LED pin */
#define GREEN_LED_PIN F6

/* Speaker pin */
#define SPEAKER_PIN B6

/* Serial communication for Web Game */
#define SERIAL_USART_BAUD 9600

