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

bool process_record_custom_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_BWRD:
            tap_code16(layer_state_is(_WIN) ? C(KC_BSPC) : LOPT(KC_BSPC));
            return true;

        case CK_HOME:
            tap_code16(layer_state_is(_WIN) ? KC_HOME : LCMD(KC_LEFT));
            return true;

        case CK_END:
            tap_code16(layer_state_is(_WIN) ? KC_END : LCMD(KC_RGHT));
            return true;

        case CK_VOLU:
            tap_code16(layer_state_is(_WIN) ? KC_VOLU : LOPT(S(KC_KB_VOLUME_UP)));
            return true;

        case CK_VOLD:
            tap_code16(layer_state_is(_WIN) ? KC_VOLD : LOPT(S(KC_KB_VOLUME_DOWN)));
            return true;

        case CK_DLFT:
            tap_code16(layer_state_is(_WIN) ? C(LWIN(KC_LEFT)) : C(KC_LEFT));
            return true;

        case CK_DRHT:
            tap_code16(layer_state_is(_WIN) ? C(LWIN(KC_RGHT)) : C(KC_RGHT));
            return true;

        case CK_LWRD:
            tap_code16(layer_state_is(_WIN) ? C(KC_LEFT) : LOPT(KC_LEFT));
            return true;

        case CK_RWRD:
            tap_code16(layer_state_is(_WIN) ? C(KC_RGHT) : LOPT(KC_RGHT));
            return true;

        case CK_COMP:
            send_string("qmk compile");
            tap_code(KC_ENT);
            return true;

        case CK_FLSH:
            send_string("qmk flash");
            tap_code(KC_ENT);
            return true;
    }
    return true;
}
