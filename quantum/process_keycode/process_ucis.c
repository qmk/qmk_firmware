/* Copyright 2017 Jack Humbert
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

#include "process_ucis.h"
#include "ucis.h"
#include "keycodes.h"

bool process_ucis(uint16_t keycode, keyrecord_t *record) {
    if (ucis_active() && record->event.pressed) {
        bool special = keycode == KC_SPACE || keycode == KC_ENTER || keycode == KC_ESCAPE || keycode == KC_BACKSPACE;
        if (ucis_count() >= UCIS_MAX_INPUT_LENGTH && !special) {
            return false;
        }

        if (!ucis_add(keycode)) {
            switch (keycode) {
                case KC_BACKSPACE:
                    return ucis_remove_last();
                case KC_ESCAPE:
                    ucis_cancel();
                    return false;
                case KC_SPACE:
                case KC_ENTER:
                    ucis_finish();
                    return false;
            }
        }
    }

    return true;
}
