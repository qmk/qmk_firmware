/*
Copyright 2020 Copyright 2020 Draevin Luke <contact@drae.vin> @draevin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "draevin.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CM_QW: // Switch between Colemak and QWERTY
            if (record->event.pressed) {
                layer_invert(_CM);
                layer_invert(_QW);
            }
            return false;
        case KC_MAKE:
            if (!record->event.pressed) {
                SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash\n");
                reset_keyboard();
            }
            break;
        case PRNPAIR:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            break;
        case BRCPAIR:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                        SEND_STRING("{}"SS_TAP(X_LEFT));
                    }
                    else {
                        SEND_STRING("[]"SS_TAP(X_LEFT));
                    }
            }
            break;
    }
    return true;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)  // shift/caps TD
};
