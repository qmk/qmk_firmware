/*
Copyright 2021 Moritz Plattner
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
#define VENDOR_ID       0x4C58      //"LX"
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    Lx3
#define PRODUCT         FAVE-87

/* Force USB NKRO */
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { D3, D5, D1, D2, D4, D0, F5, F4, F7, F6, B5, B4 }
#define MATRIX_COL_PINS { F1, F0, E6, B0, B1, B2, B3, D6, D7 }
#define UNUSED_PINS { B6, C6, C7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Backlight */
#define BACKLIGHT_PIN B7 // Timer 1 on mega32u4
#define BACKLIGHT_BREATHING
#define BACKLIGHT_ON_STATE 1

/* Underglow */
#define RGB_DI_PIN E2
#define RGBLED_NUM 40
#define RGBLIGHT_SLEEP // Turns LEDs off if the PC goes to sleep/shutdown
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
