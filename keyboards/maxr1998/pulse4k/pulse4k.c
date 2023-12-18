/*
 * Copyright (C) 2019-2020  Maxr1998 <max.rumpf1998@gmail.com>
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

#include "pulse4k.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;

    if (index == 0) {
        encoder_one_update(clockwise);
    } else if (index == 1) {
        encoder_two_update(clockwise);
    }
    return true;
}

__attribute__((weak)) void encoder_one_update(bool clockwise) {
    tap_code(!clockwise ? KC_PGUP : KC_PGDN);
}

__attribute__((weak)) void encoder_two_update(bool clockwise) {
    tap_code(!clockwise ? KC_VOLD : KC_VOLU);
}
