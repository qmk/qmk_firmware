/* 
Copyright 2023 Qwertykeys

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

#define RGBLIGHT_LAYERS_RETAIN_VAL      
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL + 5

/*== customize breathing effect ==*/
#define RGBLIGHT_BREATHE_TABLE_SIZE 128
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.0
#define RGBLIGHT_EFFECT_BREATHE_MAX    60

/* RGB matrix */
#define I2C1_CLOCK_SPEED 400000  
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_GND

#define RGB_MATRIX_DISABLE_KEYCODES 
