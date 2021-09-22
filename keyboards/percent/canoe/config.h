/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#ifndef CANOE_CONFIG_H
#define CANOE_CONFIG_H

#include "config_common.h"

#define VENDOR_ID       0x5053 /* PS */
#define PRODUCT_ID      0x434E
#define DEVICE_VER      0x0200
#define MANUFACTURER    Percent Studios
#define PRODUCT         CANOE

#define RGBLED_NUM 2

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN D1

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

#define RGBLIGHT_ANIMATIONS

#endif
