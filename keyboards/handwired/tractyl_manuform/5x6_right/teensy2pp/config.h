/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

// wiring of each half
#define MATRIX_COL_PINS \
    { C0, C1, C2, C3, C4, C5 }
#define MATRIX_ROW_PINS \
    { F7, F6, F5, F4, F3, F2 }

#define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN      E7
#define RGBLED_NUM      20
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 10, 10 }
#define RGBLIGHT_LIMIT_VAL 80
#define OLED_BRIGHTNESS    50

#define DEBUG_LED_PIN   D6

#define AUDIO_PIN       C6
#define AUDIO_PIN_ALT   B7

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

#define ENCODERS_PAD_A \
    { D5 }
#define ENCODERS_PAD_B \
    { D4 }

/* PMW33XX Settings */
#define PMW33XX_CS_PIN B0
