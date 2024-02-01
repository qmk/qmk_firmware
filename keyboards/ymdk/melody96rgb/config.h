#pragma once

#define DEBOUNCE 6

/* key matrix size */
//#define MATRIX_ROWS 12
//#define MATRIX_COLS 9

/* key matrix pins */
//#define MATRIX_ROW_PINS { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
//#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }

/* COL2ROW or ROW2COL */
//#define DIODE_DIRECTION ROW2COL

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//#define PREVENT_STUCK_MODIFIERS
//#define DEBOUNCE 5
//#ifdef RGB_MATRIX_ENABLE 
// The pin connected to the data pin of the LEDs
// #define RGB_DI_PIN E2
// The number of LEDs connected
#define DRIVER_LED_TOTAL 118
#define RGB_MATRIX_LED_COUNT 118
 
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80     // 最大亮度限制
#define RGB_MATRIX_CENTER { 108, 32 }
//#endif

#define CAPS_LOCK_LED_INDEX 55
#define NUM_LOCK_LED_INDEX 33
