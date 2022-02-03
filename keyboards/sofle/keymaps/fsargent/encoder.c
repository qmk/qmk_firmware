/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

// Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.

#ifdef ENCODER_ENABLE

// enum layers { BASE, WIN, GAME, SYM, NAV, WINNAV};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(SYM)) {  // on Nav layer controls window
        if (index == 0) {
            if (reversed) {
                if (clockwise) {
                    tap_code16(KC_RIGHT);
                } else {
                    tap_code16(KC_LEFT);
                }
            } else {
                if (clockwise) {
                    tap_code16(KC_UP);
                } else {
                    tap_code16(KC_DOWN);
                }
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_MNXT);
            }
        }
    } else if (IS_LAYER_ON(NAV)) {  // on Nav layer controls window
        if (index == 0) {
            if (reversed) {
                if (clockwise) {
                    tap_code16(KC_RIGHT);
                } else {
                    tap_code16(KC_LEFT);
                }
            } else {
                if (clockwise) {
                    tap_code16(KC_UP);
                } else {
                    tap_code16(KC_DOWN);
                }
            }
        } else if (index == 1) {
             if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
        }
    } else {  // on other layers browser  tab switching
        if (index == 0) {
            if (reversed) {
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(C(S(KC_TAB)));
                }
            } else {
                if (clockwise) {
                    tap_code16(G(S(KC_GRV)));
                } else {
                    tap_code16(G(KC_GRV));
                }
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
        }
    }
    return true;
}
#endif
