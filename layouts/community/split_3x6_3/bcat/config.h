/* Copyright 2020 Jonathan Rascher
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

#if defined(KEYBOARD_crkbd_rev1_common) || defined(KEYBOARD_crkbd_rev1_legacy)
#    define EE_HANDS

#    if defined(RGBLIGHT_ENABLE)
/* Configure RGB for underglow only (first six LEDs on each side). */
#        undef RGBLED_SPLIT
#        define RGBLED_SPLIT \
            { 6, 6 }
#    endif

#    if defined(RGB_MATRIX_ENABLE)
/* Limit max RGB LED current to avoid tripping controller fuse. */
#        undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    endif
#endif
