/*
Copyright 2021 Tyler Tolley <thattolleyguy@gmail.com>

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

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS
// Rows are doubled-up

#undef RGB_DI_PIN
#define RGB_DI_PIN F5

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D0
// #define RGB_MATRIX_LED_COUNT 32

#define RGB_MATRIX_KEYPRESSES

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80
#undef RGBLED_NUM
#define RGBLED_NUM       64 // Number of LEDs
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#define RGB_MATRIX_SPLIT \
        { 32, 32  }
#define SPLIT_TRANSPORT_MIRROR

// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP // Sets the default mode, if none has been set
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif
