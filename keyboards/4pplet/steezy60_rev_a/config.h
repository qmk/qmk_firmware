#ifndef CONFIG_H
#define CONFIG_H

// Used Plan60 as template
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         Steezy60 Rev A
#define DESCRIPTION     A steezy keeb

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {C2,D0,B0,C7,C5}
#define MATRIX_COL_PINS {C4,C6,B7,B6,B5,B4,B3,B2,B1,D6,D5,D4,D2,D1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT C4 // usually COL
#define QMK_ESC_INPUT C2 // usually ROW

#define GRAVE_ESC_CTRL_OVERRIDE
#define GRAVE_ESC_ALT_OVERRIDE
#define GRAVE_ESC_GUI_OVERRIDE
#define GRAVE_ESC_SHIFT_OVERRIDE

#define RGB_DI_PIN D3
#define RGBLED_NUM 12
#define BACKLIGHT_LEVELS 5

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_ANIMATIONS

#endif
