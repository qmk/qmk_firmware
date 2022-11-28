/*
Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "custom_keycodes.h"
#include "mreel.h"

bool process_record_parity(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // App switching with ctrl instead of alt on windows
        case KC_TAB:
            if (record->event.pressed && ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL))) {
                set_mods(MOD_BIT(KC_LALT));
            }
            return true;
        case KC_LCTL:
            if (!record->event.pressed && ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT))) {
                unregister_code(KC_LALT);
                return false;
            }
            return true;

        // Close App and Lock using MacOS shortcuts (ctrl+Q and win+ctrl+Q)
        case KC_Q:
            if (record->event.pressed) {
                if ((get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI))) == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI))) {
                    clear_mods();
                    tap_code16(G(KC_L));
                    return false;
                } else if ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    clear_mods();
                    tap_code16(A(KC_F4));
                    set_mods(MOD_BIT(KC_LCTL));
                    return false;
                }
            }
    }
    return true;
}

// 1: On the windows layer, ctrl is on the same pos as command on mac (KC_LGUI)
