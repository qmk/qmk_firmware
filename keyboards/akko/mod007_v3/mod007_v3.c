/* Copyright (C) 2022 jonylee@hfd
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

#include "quantum.h"

// clang-format off
enum __layers {
    WIN_B,
    WIN_W,
    WIN_FN,
    MAC_B,
    MAC_W,
    MAC_FN
};
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case DF(WIN_B):
            if ( record->event.pressed) {
                set_single_persistent_default_layer(WIN_B);
                layer_state_set(1<<WIN_B);
            }
            return false;
        case DF(MAC_B):
            if (record->event.pressed) {
                set_single_persistent_default_layer(MAC_B);
                layer_state_set(1<<MAC_B);
                keymap_config.no_gui     = 0;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        default:
            return true;
    }
}