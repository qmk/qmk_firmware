/* Copyright 2021 Conor Burns
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

enum layer_names {
  _HOME,
  _FN2,
  _FN3,
  _FN4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HOME] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DEL,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  MO(1),   KC_SPC,           KC_RALT, KC_RCTL,                     KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN2] = LAYOUT(
        _______, KC_F1,   KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,     KC_F11,  KC_F12,  _______, _______, _______,
        _______,          _______,    _______, _______, _______, _______, _______, RALT(KC_U), _______, RALT(KC_O), _______, _______, _______, _______, _______,
        _______,          _______,    _______, _______, _______, _______, _______, _______,    _______, _______,    _______, _______, _______,          _______,
        _______, _______, RALT(KC_A), _______, _______, _______, _______, _______, _______,    _______, _______,    _______, _______,          _______, _______,
        _______, _______, _______,                      MO(2),   _______, _______,             _______, _______,                      _______, _______, _______
    ),
    [_FN3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                   _______, _______, MO(3),            _______, _______,                   _______, _______, _______
    ),
    [_FN4] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                   _______, _______, _______,          _______, _______,                   _______, _______, _______
    ),
};

// RGB LED Indicators
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_PURPLE}    // Light 3 LEDs, starting with LED 0
);
const rgblight_segment_t PROGMEM my_2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, HSV_PURPLE}    // Light 1 LED, starting with LED 3
);
const rgblight_segment_t PROGMEM my_3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 1, HSV_PURPLE}    // Light 1 LED, starting with LED 4
);
const rgblight_segment_t PROGMEM my_4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_PURPLE}    // Light 1 LED, starting with LED 5
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,  // 0
    my_2_layer,  // 1
    my_3_layer,  // 2
    my_4_layer  // 3
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _FN3));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FN4));
    return state;
}