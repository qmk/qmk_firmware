#ifndef STAPELBERG_CONFIG_H
#define STAPELBERG_CONFIG_H

#include "../config.h"

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
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D4, D5, D6, D7, C0, C1, C2, C3, C4, C5, C6 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN F2
#define LED_CAPS_LOCK_PIN F3
#define LED_SCROLL_LOCK_PIN F1
#define LED_COMPOSE_PIN F0
#define LED_PIN_ON_STATE 0

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* don't know if this should be defined at the board or top level. Assuming board 
#define MOUSEKEY_DELAY          100
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED      3
#define MOUSEKEY_TIME_TO_MAX    10
*/

#define IGNORE_MOD_TAP_INTERRUPT

#endif
