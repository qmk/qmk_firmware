/*
Copyright 2023 seflm (@seflm)

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

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

//Digital joystick (4-way switch + encoder)
#define PIN_JU D4
#define PIN_JD B6
#define PIN_JL D7
#define PIN_JR B4
#define PIN_JC C6

//Thumbwheel
#define PIN_TC D2

//Thumbwheel and joystick encoders
#define ENCODERS_PAD_A { D6, D1 }
#define ENCODERS_PAD_B { B5, D0 }
#define ENCODER_RESOLUTIONS { 2, 2 }

//Backlighting
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_LIMIT_VAL 192
#define BACKLIGHT_BREATHING
#define BACKLIGHT_DEFAULT_LEVEL 5

//RGB ring
#define RGB_DI_PIN D3
#define RGBLED_NUM 5
#define RGBLIGHT_DEFAULT_VAL 64
#define RGBLIGHT_LIMIT_VAL 192
#define RGBLIGHT_SLEEP