#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1701
#define DEVICE_VER      0x0203
#define MANUFACTURER    MechWild
#define PRODUCT         BDE Lefty
#define DESCRIPTION     41-key ortholinear 30% with southpaw numpad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D7, D3}
#define MATRIX_COL_PINS { F7, B1, B6, B2, B3, F6, F5, F4, D0, D4, C6, E6, B5, B4}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* If RGBLIGHT_ENABLE is set to yes in the rules,  ensure the RGBLED_NUM is accurate for how many you have attached. */
#define RGB_DI_PIN D2
#define RGBLED_NUM 16 
#define RGBLIGHT_ANIMATIONS

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Making it so you need to hold the modifier and other key for the time together, helps not accidentally hit activate the hold functions of bottom row*/
#define IGNORE_MOD_TAP_INTERRUPT

/* Setting tap term, helps not accidentally hit activate the hold functions of bottom row*/
#define TAPPING_TERM 250