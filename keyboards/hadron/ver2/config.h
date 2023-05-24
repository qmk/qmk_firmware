/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0002

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Hadron Ver0 PCB default pin-out */
#define MATRIX_ROW_PINS { D7, E6, B4, B5, B6 }
#define MATRIX_COL_PINS { F6, F7, D6, C7, F5, F4, F1, F0, D2, D3, D5, B3, B2, B1, B0 }
#define UNUSED_PINS

// configure oled driver for the 128x32 oled
#define OLED_UPDATE_INTERVAL 33 // ~30fps

/* ws2812 RGB LED*/
#define RGB_DI_PIN D4
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17


