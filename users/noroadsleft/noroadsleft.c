/* Copyright 2020 noroadsleft
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

#include "noroadsleft.h"
#include "version.h"

enum userspace_keycodes {
    NUBS_Z = SAFE_RANGE,
    VRSN,
    KEYMAP_SAFE_RANGE
};

/*******************
** MODIFIER MASKS **
*******************/
#define MOD_MASK_RALT (MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUBS_Z:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_RALT) {
                    SEND_STRING(SS_DOWN(X_NONUS_BSLASH));
                } else {
                    SEND_STRING(SS_DOWN(X_Z));
                }
            } else {
                if (get_mods() & MOD_MASK_RALT) {
                    SEND_STRING(SS_UP(X_NONUS_BSLASH));
                } else {
                    SEND_STRING(SS_UP(X_Z));
                }
            };
            return false;
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            return false;
        case KC_1 ... KC_0:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_RALT) {
                    register_code(keycode + 0x3B);
                } else {
                    register_code(keycode);
                }
            } else {
                if (get_mods() & MOD_MASK_RALT) {
                    unregister_code(keycode + 0x3B);
                } else {
                    unregister_code(keycode);
                }
            }
            return false;
        case KC_F1 ... KC_F12:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_RALT) {
                    register_code(keycode + 0x2E);
                } else {
                    register_code(keycode);
                }
            } else {
                if (get_mods() & MOD_MASK_RALT) {
                    unregister_code(keycode + 0x2E);
                } else {
                    unregister_code(keycode);
                }
            }
            return false;
    }  // switch()
    return process_record_keymap(keycode, record);
};
