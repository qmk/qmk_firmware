/* Copyright 2018 Salicylic_acid3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 180

#ifdef RGBLIGHT_LED_COUNT
  #undef RGBLIGHT_LED_COUNT
#endif

#define RGBLIGHT_LED_COUNT 55    // Number of LEDs
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 48, 7 }

