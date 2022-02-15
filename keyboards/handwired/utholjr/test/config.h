/*
 * Copyright 2021 Uthol
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

#define DEVICE_VER      0x0001
#define PRODUCT_ID      0x67F3
#define PRODUCT         UtholJR-Test

/* UtholJR default pin-out */
#define MATRIX_COL_PINS { D3, D2, D4, F4, C6, D7, B5, B4, B6, B2, B3, E6 }
#define MATRIX_ROW_PINS { B1, F7, F6, F5 }


//OLED config
#define OLED_DISPLAY_128X64
#define OLED_UPDATE_INTERVAL 0
#define OLED_BRIGHTNESS 255
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_RESET     -1