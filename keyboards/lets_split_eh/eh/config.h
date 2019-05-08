/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef EH_CONFIG_H
#define EH_CONFIG_H

// To let configuration know this is of type EH, which will force I2C irregardless of user config
#define EH
// The 'EH' only uses I2C
#define USE_I2C

#include "config_common.h"

/* Let's Split EH? pin-out */
#define MATRIX_ROW_PINS { B1, B3, D7, B4 }
#define MATRIX_COL_PINS { F4, F5, C6, B6, B5, D5 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

/* ws2812 RGB LED */
#define RGB_DI_PIN B2
#define RGBLED_NUM 6    // Number of LEDs (each hand)

/* Split Defines */
#define SPLIT_HAND_PIN D3

#endif

