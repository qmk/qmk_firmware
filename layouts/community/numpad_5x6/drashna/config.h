/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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


#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#    define RGB_DI_PIN B1
#    define RGBLED_NUM 16  // Number of LEDs

#    define RGBLIGHT_HUE_STEP 12
#    define RGBLIGHT_SAT_STEP 12
#    define RGBLIGHT_VAL_STEP 12
#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#endif  // RGBLIGHT_ENABLE

#define RGBLIGHT_ALL_ANIMATIONS

#if defined(KEYBOARD_primekb_prime_m)
#    undef PRODUCT
#    define PRODUCT Drashna Hacked Prime_M Macro Pad
#endif
