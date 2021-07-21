/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Use I2C or Serial, not both */
#include "../drashna/config.h"

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLED_NUM 16  // Number of LEDs
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 8, 8 }
#endif

#undef PRODUCT
#ifdef KEYBOARD_keebio_iris_rev2
#    define PRODUCT Drashna Hacked Iris LP Rev .2(Backlit)
#endif

#undef SHFT_LED1
#define SHFT_LED1 5
#undef SHFT_LED2
#define SHFT_LED2 10

#undef CTRL_LED1
#define CTRL_LED1 6
#undef CTRL_LED2
#define CTRL_LED2 9

#undef ALT_LED1
#define ALT_LED1 7
#undef GUI_LED1
#define GUI_LED1 8

#define DRASHNA_LP
