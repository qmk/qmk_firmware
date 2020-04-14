/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Wayne Jones (WarmCatUK) <waynekjones@gmail.com>

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

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define DEVICE_VER      0x0200
#define MANUFACTURER    KPrepublic
#define PRODUCT         JJ50
#define DESCRIPTION     Preonic-like clone

/* matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 12

#define RGB_DI_PIN E2
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 15
#define RGBLIGHT_VAL_STEP 18

#endif
