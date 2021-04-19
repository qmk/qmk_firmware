/*
Copyright 2020 Adam Honse <calcprogrammer1@gmail.com>
Copyright 2020 Dimitris Mantzouranis <d3xter93@gmail.com>

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

// Backlight configuration
#define BACKLIGHT_LEVELS 8

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)
//note how ROW pins are assined in the following sequence top down row1 RBG, row2 RBG and so on
#define LED_MATRIX_ROW_PINS { C6, C5, C4, C9, C8, C7, C12, C11, C10, B13, C14, C13, B14, B15, D3 }

#define LED_MATRIX_COLS 16
#define LED_MATRIX_COLUMNS LED_MATRIX_COLS
#define LED_MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7 }

#define DRIVER_LED_TOTAL (LED_MATRIX_ROWS * LED_MATRIX_COLS)

//#define RGB_MATRIX_ENABLE 1
//#define RGB_MATRIX_KEYPRESSES
//#define RGB_MATRIX_LED_PROCESS_LIMIT 0
//#define RGB_MATRIX_LED_FLUSH_LIMIT 0 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_HUE 127 // Sets the default hue value, if none has been set
#define RGB_MATRIX_STARTUP_SAT 0   // Sets the default saturation value, if none has been set
#define RGB_MATRIX_STARTUP_VAL 255 // Sets the default brightness value, if none has been set
#define RGB_MATRIX_STARTUP_SPD 63
#define RGB_MATRIX_SPD_STEP 16

#define SLEEP_LED_MODE_ANIMATION RGB_MATRIX_BREATHING
