/* Copyright 2024 leep-frog
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

#include "quantum.h"
#include "housekeeping_keyboard.h"

// clang-format off

bool do_housekeeping = false;

void housekeeping_task_user(void) {
    if (do_housekeeping) {
        do_housekeeping = false;
        tap_code16(KC_I);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_H && !record->event.pressed) {
        do_housekeeping = true;
    }
    return true;
}

// clang-format on
