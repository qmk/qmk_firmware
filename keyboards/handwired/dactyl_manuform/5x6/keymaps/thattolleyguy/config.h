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

#define EE_HANDS

#define WS2812_DI_PIN F5
#define SOFT_SERIAL_PIN D0
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_LED_COUNT 64  
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80
#define RGB_MATRIX_SPLIT { 32, 32 }
#define SPLIT_TRANSPORT_MIRROR
// #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP // Sets the default mode, if none has been set
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
