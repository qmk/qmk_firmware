/*
Copyright 2020 Team Mechlovin'

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

#define PRODUCT      Adelais

#define MATRIX_ROW_PINS { B1, A0, C13, A1, A2}
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B8, B4, B5, B3, C14, A15 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B0
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define RGB_DI_PIN A7
#define RGBLED_NUM 23
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_ANIMATIONS


#define LED_NUM_LOCK_PIN C15
#define LED_CAPS_LOCK_PIN B2
#define LED_SCROLL_LOCK_PIN B9
