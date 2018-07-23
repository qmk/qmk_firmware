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

#ifndef PROTO_CONFIG_H
#define PROTO_CONFIG_H

#include "config_common.h"

// wiring of each half
#define MATRIX_ROW_PINS { F4, F5, C6, D7, E6 }
#define MATRIX_COL_PINS { F7, F6, B1, B3, B2, B6, B5, B4 }
#define DIODE_DIRECTION ROW2COL

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLED_NUM 1    // Number of LEDs
// #define ws2812_PORTREG  PORTD
// #define ws2812_DDRREG   DDRD


#endif
