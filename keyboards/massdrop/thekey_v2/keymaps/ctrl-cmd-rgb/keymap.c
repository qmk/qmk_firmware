/* Copyright 2023 ShizukuIchi <shizukuichi@gmail.com>
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

#define HIGHEST_LAYER 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_LCTL, KC_C, KC_V),
    [1] = LAYOUT(KC_LCMD, KC_C, KC_V),
    [2] = LAYOUT(RGB_TOG, RGB_MOD, RGB_RMOD),
};

enum combos {
    SWITCH_LAYER,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM switch_layer_combo[] = {KC_LCTL, KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    [SWITCH_LAYER] = COMBO_ACTION(switch_layer_combo),
};

uint16_t layer = 0;

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SWITCH_LAYER:
            if (pressed) {
                layer++;
                if (layer <= HIGHEST_LAYER) {
                    layer_on(layer);
                } else {
                    layer_move(0);
                    layer = 0;
                }
            }
            break;
    }
}
