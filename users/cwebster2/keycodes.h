/* Copyright 2020 Casey Webster <casey@e1337.dev>
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

#include QMK_KEYBOARD_H

enum userspace_custom_keycodes {
    KC_LCCL = SAFE_RANGE,
    NEW_SAFE_RANGE
};

#define KC_CTLBS CTL_T(KC_BSPC)
#define KC_ALTCL LALT_T(KC_CAPS)
#define KC_LOCK  LGUI(LCTL(KC_L))
