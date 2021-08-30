/*
Copyright 2021 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x111C
#define DEVICE_VER      0x0100
#define MANUFACTURER    Keebio
#define PRODUCT         The Stick

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 12

/* key matrix pins */
#define DIRECT_PINS { \
    { F4, B6, B5, B4, E6, D7, F6, F7, B1, B3, B2, F5 } \
}

#define ENCODERS_PAD_A { D1, D4 }
#define ENCODERS_PAD_B { D0, C6 }

/* WS2812 RGB LED */
#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 12
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
// RGB Matrix
#    ifdef RGB_MATRIX_ENABLE
#        define DRIVER_LED_TOTAL RGBLED_NUM
#    endif
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200
