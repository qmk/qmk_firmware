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

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 12

#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 3
#    ifdef RGB_MATRIX_ENABLE
#        define RGBLIGHT_DISABLE_KEYCODES
#    endif
#endif  // RGBLIGHT_ENABLE

#undef PRODUCT
#define PRODUCT DrashnaDox - Hacked ErgoDox EZ Hybrid Monstrosity

#undef DEBOUNCE
#define DEBOUNCE 20

#define TAPPING_TERM_PER_KEY

#define ERGODOX_LED_30

#ifdef RGB_MATRIX_ENABLE
#    undef RGB_MATRIX_LED_PROCESS_LIMIT
#    undef RGB_MATRIX_LED_FLUSH_LIMIT
#    if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
#        define RGBLIGHT_LIMIT_VAL 100
#    endif
#endif

#define PIMORONI_TRACKBALL_INVERT_X
#define PIMORONI_TRACKBALL_INVERT_Y
