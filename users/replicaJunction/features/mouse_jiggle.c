/* Copyright 2021 Joshua T.
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

#include "mouse_jiggle.h"

bool is_mouse_jiggle_active = false;

void matrix_scan_mouse_jiggle(void) {
    if (is_mouse_jiggle_active) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
    }
}

bool process_record_mouse_jiggle(uint16_t keycode, const keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (is_mouse_jiggle_active) {
        // If active, quit whenever another key is pressed
        is_mouse_jiggle_active = false;
        return true;
    }

    if (keycode != MS_JIGL) {
        return true;
    }

    is_mouse_jiggle_active = true;
    SEND_STRING("Mouse jiggler enabled");
    return false;
}
