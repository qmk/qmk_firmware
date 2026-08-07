/* Copyright 2021 Ananya Kirti
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

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x3(
        KC_CAPS,  MO(1), KC_PGUP,
        KC_DEL,  KC_END,  KC_PGDN
    ),
    [1] = LAYOUT_ortho_2x3(
        KC_CAPS,  MO(1), KC_PGUP,
        KC_DEL,  KC_END,  KC_PGDN
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(D0, IS_LAYER_ON_STATE(state, 1));
    
    return state;
}
