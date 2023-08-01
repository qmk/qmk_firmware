/* Copyright 2020 Guillaume Gérard
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
#include "programmer.h"

bool process_record_pg(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY_PROGRAMMER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_PROGRAMMER);
            }
            return false;
        case WORKMAN_PROGRAMMER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN_PROGRAMMER);
            }
            return false;
        case COLEMAK_PROGRAMMER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_PROGRAMMER);
            }
            return false;
        case DVORAK_PROGRAMMER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK_PROGRAMMER);
            }
            return false;
        case PG_GRV:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("`");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("~");
                }
            }
            return false;
        case PG_1:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("1");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("!");
                }
            }
            return false;
        case PG_2:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("2");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("@");
                }
            }
            return false;
        case PG_3:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("3");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("#");
                }
            }
            return false;
        case PG_4:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("4");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("$");
                }
            }
            return false;
        case PG_5:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("5");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("%");
                }
            }
            return false;
        case PG_6:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("6");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("^");
                }
            }
            return false;
        case PG_7:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("7");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("&");
                }
            }
            return false;
        case PG_8:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("8");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("*");
                }
            }
            return false;
        case PG_9:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("9");
                    set_mods(current_mods);
                } else {
                    SEND_STRING("(");
                }
            }
            return false;
        case PG_0:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods();
                if (current_mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING("0");
                    set_mods(current_mods);
                } else {
                    SEND_STRING(")");
                }
            }
            return false;
    }
    return true;
}
