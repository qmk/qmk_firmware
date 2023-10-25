/* Copyright 2020 Jrodna
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
#include "orthocode.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    static bool shiftspace_mods = false;
    switch (keycode) {
    case SHIFTSPACE:
        if (record->event.pressed) {
            if(get_mods() & MOD_BIT(KC_RSFT)) {
                register_code(KC_MINS);
                shiftspace_mods = true;
            }
            else {
                register_code(KC_SPC);
            }
        } else {
            if (shiftspace_mods) {
                unregister_code(KC_MINS);
                shiftspace_mods = false;
            } else {
                unregister_code(KC_SPC);
            }
        }
        return false;
        break;
    }
    return true;
}
