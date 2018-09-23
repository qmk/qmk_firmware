/*
Copyright 2018 Cole Markham

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
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x2328
#define DEVICE_VER      0x0205
#define MANUFACTURER    K.T.E.C.
#define PRODUCT         Staryu
#define DESCRIPTION     5-key macropad

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS {  }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4 }
#define UNUSED_PINS

// from light_ws2812_config @
// https://github.com/kairyu/tmk_keyboard_custom/tree/master/keyboard/staryu
#define RGB_DI_PIN C6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 1     // Number of LEDs

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

// TODO backlighting
#define BACKLIGHT_LEVELS 10
// #define BACKLIGHT_PIN B7
/*
Backlight: C2, C7, D5, D6, B0
switch (index) {
    case 0:
        PORTC &= ~(1<<PC2);
        break;
    case 1:
        PORTC &= ~(1<<PC7);
        break;
    case 2:
        PORTD &= ~(1<<PD5);
        break;
    case 3:
        PORTD &= ~(1<<PD6);
        break;
    case 4:
        PORTB &= ~(1<<PB0);
        break;
*/

#endif
