/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 F_YUUCHI
Copyright 2023 Elliot Powell

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
//#define SERIAL_USE_MULTI_TRANSACTION


#ifdef RGB_MATRIX_ENABLE
#   define RGB_DI_PIN D3
#   define RGB_MATRIX_LED_COUNT 74
#   define RGB_DISABLE_WHEN_USB_SUSPENDED
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_KEYRELEASES
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS


#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#endif

#   define SPLIT_TRANSPORT_MIRROR
#endif

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_LIMIT_VAL 120
#endif

