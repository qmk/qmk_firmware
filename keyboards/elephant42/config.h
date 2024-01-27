/*
Copyright 2021 illness072

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

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_LED_COUNT 54
#    define RGB_MATRIX_SPLIT { 27, 27 }
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
#endif

#ifndef OLED_FONT_H
#   define OLED_FONT_H "keyboards/elephant42/lib/glcdfont.c"
#endif
