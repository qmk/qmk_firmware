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

// WS2812 RGB LED strip input and number of LEDs
#define RGB_MATRIX_LED_COUNT 62
#define RGB_MATRIX_SPLIT { 32, 30 }
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_KEYPRESSES
// #define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_HAND_PIN A6

// #define DEBUG_LED_PIN                  D6

#define ROTATIONAL_TRANSFORM_ANGLE     -25

#define AUDIO_PIN                      C6
#define AUDIO_PIN_ALT                  B7

#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095
#define DYNAMIC_KEYMAP_LAYER_COUNT     16
#define LAYER_STATE_16BIT

#define EE_HANDS

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* PMW33XX Settings */
#define PMW33XX_CS_PIN           B0

#define POINTING_DEVICE_RIGHT
