/* Copyright 2021 @ Mike Killewald
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

#ifdef CAPS_WORD_ENABLE
#   define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#   define CAPS_WORD_INDICATOR_COLOR RGB_RED
#   define CAPS_WORD_LIGHT_LOWER_LEFT_CORNER
#endif

#ifdef RGB_MATRIX_ENABLE
#    define CAPS_LOCK_INDICATOR_COLOR RGB_RED
#    define FN1_LAYER_COLOR 0xFF, 0x23, 0x00
#    define FN2_LAYER_COLOR RGB_GREEN
#endif