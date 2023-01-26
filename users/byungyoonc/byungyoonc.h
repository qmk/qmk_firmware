/* Copyright 2021 Choi Byungyoon <byungyoonc@gmail.com>
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

enum custom_keycodes {
    KC_SEC1 = SAFE_RANGE,
    KC_SEC2
};

#define KC_TASK LCTL(LSFT(KC_ESC))
#define KC_MMUT LSG(KC_A)

bool process_record_user_kb(uint16_t keycode, keyrecord_t *record);
