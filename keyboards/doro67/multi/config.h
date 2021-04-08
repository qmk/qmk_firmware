#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4250 // BP for Backprop
#define PRODUCT_ID      0x4D4C // ML for Multi
#define DEVICE_VER      0x0001
#define MANUFACTURER    Backprop Studio
#define PRODUCT         Doro67 Multi PCB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

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
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, D4, D6, D7, B4, B5, B6, C6, C7, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN E6
#define LED_PIN_ON_STATE 0

#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 7
