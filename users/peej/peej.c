/* Copyright 2020 Paul James
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

#include "peej.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = get_mods() & MOD_LSFT;

    if (record->event.pressed) {
        switch(keycode) {
            case MC_ARR:
                if (is_shifted) {
                    unregister_mods(MOD_LSFT);
                    SEND_STRING("=>");
                    register_mods(MOD_LSFT);
                } else {
                    SEND_STRING("->");
                }
                break;
            case MC_DARR:
                unregister_mods(MOD_LSFT);
                SEND_STRING("=>");
                if (is_shifted) register_mods(MOD_LSFT);
                break;
            case MC_DEQL:
                if (is_shifted) {
                    unregister_mods(MOD_LSFT);
                    SEND_STRING("!=");
                    register_mods(MOD_LSFT);
                } else {
                    SEND_STRING("==");
                }
                break;
            case MC_TEQL:
                if (is_shifted) {
                    unregister_mods(MOD_LSFT);
                    SEND_STRING("!==");
                    register_mods(MOD_LSFT);
                } else {
                    SEND_STRING("===");
                }
                break;
            case KC_RESET:
                #ifdef RGBLIGHT_ENABLE
                    rgblight_enable_noeeprom();
                    rgblight_mode_noeeprom(1);
                    rgblight_setrgb_red();
                #endif
                reset_keyboard();
                break;
        }
    }

    return true;
};
