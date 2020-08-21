/*
Copyright 2017 Max Rumpf alias Maxr1998 <max.rumpf1998@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define RGB_DI_PIN          F4 // pin the DI on the WS2812B is hooked-up to
#define RGBLIGHT_ANIMATIONS    // run RGB animations
#define RGBLED_NUM          6  // number of LEDs
#define RGBLIGHT_HUE_STEP   12 // units to step when in/decreasing hue
#define RGBLIGHT_SAT_STEP   25 // units to step when in/decresing saturation
#define RGBLIGHT_VAL_STEP   12 // units to step when in/decreasing value (brightness)

#endif