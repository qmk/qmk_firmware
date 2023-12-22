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

#    define RGBLIGHT_LAYERS                   
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF 
#    define RGBLIGHT_LAYERS_RETAIN_VAL      
#    define RGBLIGHT_DEFAULT_VAL 10
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL + 5
#    define RGBLIGHT_SLEEP
/*== customize breathing effect ==*/
#    define RGBLIGHT_BREATHE_TABLE_SIZE 128
#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.0
#    define RGBLIGHT_EFFECT_BREATHE_MAX    60

/* RGB matrix */
#define I2C1_CLOCK_SPEED 400000  
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2  
#    define RGB_MATRIX_DISABLE_KEYCODES 
#    define RGB_MATRIX_SLEEP  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES           // reacts to keypresses
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_LED_PROCESS_LIMIT  4
#    define RGB_MATRIX_LED_FLUSH_LIMIT    26
#    define RGB_MATRIX_STARTUP_VAL        128
#    define DRIVER_ADDR_1                 0b0110000
#    define RGB_MATRIX_LED_COUNT          101 