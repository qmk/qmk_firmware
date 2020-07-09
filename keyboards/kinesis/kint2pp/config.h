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
#define MATRIX_ROW_PINS \
  {			\
   D7, /* ROW_EQL */	\
   E0, /* ROW_1 */	\
   E1, /* ROW_2 */	\
   C0, /* ROW_3 */	\
   C6, /* ROW_4 */	\
   F6, /* ROW_5 */	\
   D4, /* ROW_6 */	\
   D2, /* ROW_7 */	\
   D3, /* ROW_8 */	\
   D0, /* ROW_9 */	\
   B7, /* ROW_0 */	\
   D1, /* ROW_MIN */	\
   E6, /* ROW_ESC */	\
   B4, /* ROW_F1 */	\
   B2  /* ROW_F2 */	\
  }

#define MATRIX_COL_PINS \
  {			\
   E7, /* COL_0 */	\
   F0, /* COL_1 */	\
   F7, /* COL_2 */	\
   B1, /* COL_3 */	\
   B3, /* COL_4 */	\
   B0, /* COL_5 */	\
   D5 /* COL_6 */	\
  }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
 

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
