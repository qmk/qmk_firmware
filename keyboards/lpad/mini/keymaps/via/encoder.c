/* Copyright 2021 bululau
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

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (biton32(layer_state) == 0) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    } else if (biton32(layer_state) == 1) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    } else if (biton32(layer_state) == 2) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    }
    return true;
}

#endif
