/* Copyright 2021 Jonathan Rascher
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

#include "bcat.h"

#include "quantum.h"

static int8_t alt_tab_layer = -1;

__attribute__((weak)) void process_record_oled(uint16_t keycode, const keyrecord_t *record) {}
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_oled(keycode, record);
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        /* Alt+Tab that holds Alt until current layer is released: */
        case MC_ALTT:
            if (record->event.pressed) {
                if (alt_tab_layer < 0) {
                    alt_tab_layer = layer_switch_get_layer(record->event.key);
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        default:
            return true;
    }
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_keymap(state);
#if defined(BCAT_ORTHO_LAYERS)
    state = update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
#endif
    if (alt_tab_layer >= 0 && !layer_state_cmp(state, alt_tab_layer)) {
        unregister_code(KC_LALT);
        alt_tab_layer = -1;
    }
    return state;
}
