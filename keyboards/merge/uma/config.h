/* Copyright 2021 duoshock 
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

#include "config_common.h"

#define VENDOR_ID       0x4D65
#define PRODUCT_ID      0x3232
#define DEVICE_VER      0x0001
#define MANUFACTURER    Merge
#define PRODUCT         UM-A

#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B7 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4 }
#define UNUSED_PINS

#define BACKLIGHT_PIN C6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2
#define SPLIT_USB_DETECT
#define SPLIT_MODS_ENABLE

#define DEBOUNCE 5

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0