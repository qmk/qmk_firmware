/*
Copyright 2020 yushakobo

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

#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 150 /* The maximum brightness level */
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 4
#define RGBLIGHT_LED_MAP {\
    0, 1, 2,\
    5, 4, 3,\
    6, 7, 8,\
    9, 10, 11, 12\
}
