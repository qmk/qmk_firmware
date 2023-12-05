/* Copyright 2023 TW59420 <https://github.com/TW59420>
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

const rgblight_segment_t PROGMEM my_layer0_dfu[] = RGBLIGHT_LAYER_SEGMENTS({3, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_layer1_val[] = RGBLIGHT_LAYER_SEGMENTS({3, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM my_layer2_sat[] = RGBLIGHT_LAYER_SEGMENTS({3, 2, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer3_hue[] = RGBLIGHT_LAYER_SEGMENTS({3, 2, HSV_RED});

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(LT(3, KC_LCTL), LT(1, KC_C), LT(2, KC_V)),

    [1] = LAYOUT(RGB_VAD, KC_TRNS, RGB_VAI),

    [2] = LAYOUT(RGB_SAD, RGB_SAI, KC_TRNS),

    [3] = LAYOUT(KC_TRNS, RGB_HUD, RGB_HUI)};

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_layer0_dfu, my_layer1_val, my_layer2_sat, my_layer3_hue);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}
