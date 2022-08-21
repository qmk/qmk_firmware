/*
Copyright 2022 Kyle McCreery

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

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 7

/* Key matrix pins */
#define MATRIX_ROW_PINS { C6, D7, B4, D4, E6, B2 }
#define MATRIX_COL_PINS { B3, B1, F7, F6, F5, F4, B5 }

/* Encoder pins */
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }

/* Encoder resolution */
#define ENCODER_RESOLUTION 4

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define OLED_FONT_H "keyboards/mechwild/bde/lib/rev2.c"

#define RGB_DI_PIN B6
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 8
/*== Chosen enabled animations ==*/
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif
