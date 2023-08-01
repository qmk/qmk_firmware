/*
Copyright 2020 Obosob <obosob@riseup.net>

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

#ifdef RGBLIGHT_ENABLE
#define RGBLED_SPLIT { 6, 6 }
#define RGBLED_NUM 12
#define RGBLIGHT_LED_MAP {  0,  1,  2,  3,  4,  5, \
                           11, 10,  9,  8,  7,  6 }
#endif

#define OLED_DISPLAY_128X64

#define EE_HANDS
