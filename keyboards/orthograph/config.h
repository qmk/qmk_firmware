/*
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

/* wiring of each half */
#define EE_HANDS // need to flash eeprom with eeprom-lefthand.eep for left, etc
#define SPLIT_USB_DETECT

// disable backlight after timeout in minutes, 0 = no timeout
// #define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_STARTUP_MODE ENABLE_RGB_MATRIX_BAND_VAL

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_COUNT 1
#define RGB_MATRIX_LED_COUNT 82

// 7 + 8 + 8 + 7 + 8 + 8 = 46
// 36 + 46 = 82

#define DRIVER_1_LED_TOTAL 82
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
// #define RGB_MATRIX_KEYPRESSES

// #define ENABLE_RGB_MATRIX_ALPHAS_MODS

// #define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_MULTISPLASH


#define SPLIT_TRANSPORT_MIRROR