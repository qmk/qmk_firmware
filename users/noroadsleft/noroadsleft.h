/* Copyright 2020-2021 James Young (@noroadsleft)
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

#define MOD_MASK_RALT (MOD_BIT(KC_RALT))

enum userspace_keycodes {
    VRSN = SAFE_RANGE,
    G_PUSH,
    G_FTCH,
    G_BRCH,
    M_SALL,
    M_UNDO,
    M_CUT,
    M_COPY,
    M_PASTE,
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
