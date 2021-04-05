/* Copyright 2020 James Young (@noroadsleft)
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

/*******************
** MODIFIER MASKS **
*******************/
bool macroMode = 0;

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            return false;
        case G_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push origin ");
            };
            return false;
        case G_FTCH:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    clear_mods();
                    SEND_STRING("git pull upstream ");
                } else {
                    SEND_STRING("git fetch upstream ");
                }
            };
            return false;
        case G_BRCH:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    clear_mods();
                    SEND_STRING("master");
                } else {
                    SEND_STRING("$(git branch-name)");
                }
            };
            return false;
        case M_SALL:
            if (record->event.pressed) {
                if ( macroMode == 1 ) {
                    SEND_STRING(SS_LGUI("a"));
                } else {
                    SEND_STRING(SS_LCTL("a"));
                }
            }
            return false;
        case M_UNDO:
            if (record->event.pressed) {
                if ( macroMode == 1 ) {
                    if ( get_mods() & MOD_MASK_SHIFT ) {
                        SEND_STRING(SS_LSFT(SS_LGUI("z")));
                    } else {
                        SEND_STRING(SS_LGUI("z"));
                    }
                } else {
                    SEND_STRING(SS_LCTL("z"));
                }
            }
            return false;
        case M_CUT:
            if (record->event.pressed) {
                if ( macroMode == 1 ) {
                    SEND_STRING(SS_LGUI("x"));
                } else {
                    SEND_STRING(SS_LCTL("x"));
                }
            }
            return false;
        case M_COPY:
            if (record->event.pressed) {
                if ( macroMode == 1 ) {
                    SEND_STRING(SS_LGUI("c"));
                } else {
                    SEND_STRING(SS_LCTL("c"));
                }
            }
            return false;
        case M_PASTE:
            if (record->event.pressed) {
                if ( macroMode == 1 ) {
                    if ( get_mods() & MOD_MASK_SHIFT ) {
                        SEND_STRING(SS_LSFT(SS_LALT(SS_LGUI("v"))));
                    } else {
                        SEND_STRING(SS_LGUI("v"));
                    }
                } else {
                    SEND_STRING(SS_LCTL("v"));
                }
            }
            return false;
        case M_MDSWP:
            if (record->event.pressed) {
                macroMode ^= 1;
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
    return true;
};
