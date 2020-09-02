#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0002
#define MANUFACTURER    RominRonin CandyKeys
#define PRODUCT         Katana60 rev2
#define DESCRIPTION     QMK keyboard firmware for Katana60 rev2
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
#define MATRIX_ROW_PINS { B0, E6, D5, B4 ,B5 }
#define MATRIX_COL_PINS {F0 ,F1 ,F4 ,F5 ,F6 ,F7 ,C7 ,C6 ,B6 ,D6 ,D4 ,D3 ,D2 ,D1 ,D0 }
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW


