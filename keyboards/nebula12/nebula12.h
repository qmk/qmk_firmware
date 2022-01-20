/* Copyright 2020 Yiancar
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

#define XXX KC_NO

#include "quantum.h"
#include "../wilba_tech/wt_rgb_backlight_keycodes.h"

// This a shortcut to help you visually see your layout.

#define LAYOUT_all( \
    K00, K01, K02, \
    K10, K11, K12, \
    K20, K21, K22, \
    K30, K31, K32 \
) { \
    { K00, K01, K02, }, \
    { K10, K11, K12, }, \
    { K20, K21, K22, }, \
    { K30, K31, K32, }  \
}
