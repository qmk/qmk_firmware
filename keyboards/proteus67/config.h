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

#define ENCODER_DIRECTION_FLIP
#define ENCODER_MAP_KEY_DELAY 10
#define ENCODER_DEFAULT_POS 0x3
#define RGB_DISABLE_TIMEOUT 900000 // milliseconds
#define RGB_DISABLE_WHEN_USB_SUSPENDED 1
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 3
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
