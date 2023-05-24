/*
Copyright 2020 KnoblesseOblige

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
#define VENDOR_ID    0x503D /* "P3D" */
#define PRODUCT_ID   0x5457 /* "TW" */
#define DEVICE_VER   0x0001
#define MANUFACTURER KnoblesseOblige
#define PRODUCT      TW40

#define MATRIX_ROWS 4
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B0, D5, D3, D2 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E6
#define RGBLED_NUM 15
#define RGBLIGHT_ANIMATIONS

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE

#define LOCKING_RESYNC_ENABLE
