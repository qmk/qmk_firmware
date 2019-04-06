/*
Copyright 2018 Yiancar

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

/* Include overwrites for specific keymap */

#define HS60_HHKB
#undef  PRODUCT_ID
#define PRODUCT_ID      0x4855

#undef  RGB_BACKLIGHT_ALPHAS_MODS_ROW_0
#undef  RGB_BACKLIGHT_ALPHAS_MODS_ROW_1
#undef  RGB_BACKLIGHT_ALPHAS_MODS_ROW_2
#undef  RGB_BACKLIGHT_ALPHAS_MODS_ROW_3
#undef  RGB_BACKLIGHT_ALPHAS_MODS_ROW_4
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0000000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0000000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0011000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0011000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b0011100000000111

#undef RGB_BACKLIGHT_CAPS_LOCK_INDICATOR
#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR { .color = { .h = 0, .s = 255 }, .index = 3-1 } //red
