/* Copyright 2020 Kyle McCreery 
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

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D7, D3}
#define MATRIX_COL_PINS { F7, B1, B6, B2, B3, F6, F5, F4, D0, D4, C6, E6, B5, B4}

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

