/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define TAPPING_TERM 200

#ifdef RGB_MATRIX_ENABLE
    #define SPLIT_LAYER_STATE_ENABLE
    #define RGB_MATRIX_KEYPRESSES
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE // Sets the default mode, if none has been set
    #define RGB_MATRIX_STARTUP_HUE 170 // Sets the default hue value, if none has been set
    #define RGB_MATRIX_STARTUP_SAT 200 // Sets the default saturation value, if none has been set
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
