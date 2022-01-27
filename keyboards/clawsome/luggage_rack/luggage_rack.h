/* Copyright 2021 AAClawson (AlisGraveNil)
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

#include "quantum.h"

#define LAYOUT( \
    K00, K11, K02,   \
    K20, K31, K22,   \
    K40, K51, K42,   \
                     \
         K61,        \
    K70, K81, K72    \
) { \
    { K00,   KC_NO, K02   }, \
    { KC_NO, K11,   KC_NO }, \
    { K20,   KC_NO, K22   }, \
    { KC_NO, K31,   KC_NO }, \
    { K40,   KC_NO, K42   }, \
    { KC_NO, K51,   KC_NO }, \
    { KC_NO, K61,   KC_NO }, \
    { K70,   KC_NO, K72   }, \
    { KC_NO, K81,   KC_NO }, \
}
