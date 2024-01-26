/* Copyright 2023 str studio
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

#include "oled.c"

enum custom_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _NUMBER,
    _LOWER
};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    CYCLE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * NUMBER
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * |   7  |   8  |   9  |   -  |
 * |------+------+------+------|
 * |   4  |   5  |   6  |   +  |
 * |------+------+------+------|
 * |   1  |   2  |   3  |  En  |
 * |--------------------|  te  |
 * | LOWR |   0  |  Del |  r   |
 * `---------------------------'
 */

[_NUMBER] = LAYOUT(
                                        KC_MUTE,
   KC_KP_7,     KC_KP_8,    KC_KP_9,    KC_KP_MINUS,
   KC_KP_4,     KC_KP_5,    KC_KP_6,    KC_KP_PLUS,
   KC_KP_1,     KC_KP_2,    KC_KP_3,    KC_KP_ENTER,
   MO(_LOWER),  KC_KP_0,    KC_KP_DOT
),

/* LOWER
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * | Nlck |  Up  |   *  |   /  |
 * |------+------+------+------|
 * | Left | Down | Rght |   *  |
 * |------+------+------+------|
 * | Left | Down | Rght |  En  |
 * |--------------------|  te  |
 * |  Fn  |   0  |  Del |  r   |
 * `---------------------------'
 */
 
[_LOWER] = LAYOUT(
                                            KC_MUTE,
   KC_NUM_LOCK, KC_UP,       KC_KP_ASTERISK, KC_KP_SLASH,
   KC_LEFT,     KC_DOWN,     KC_RGHT,        KC_KP_ASTERISK,
   KC_LEFT,     KC_DOWN,     KC_RGHT,        KC_KP_ENTER,
   MO(_LOWER),  KC_KP_0,     KC_KP_DOT
)

};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _LOWER);
// }

#ifdef ENCODER_ENABLE

// // Define your encoder actions
// enum encoder_action {
//     ENCODER_VOLUME,
//     ENCODER_SCROLL,
//     // Add more actions as needed
// };

// // Define a map for the encoder actions
// const uint16_t PROGMEM encoder_map[][2] = {
//     [ENCODER_VOLUME] = {KC_VOLU, KC_VOLD},
//     [ENCODER_SCROLL] = {KC_PGUP, KC_PGDN},
//     // Add more mappings as needed
// };

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index < sizeof(encoder_map) / sizeof(encoder_map[0])) {
//         uint16_t keycode = encoder_map[index][clockwise ? 0 : 1];
//         tap_code(keycode);
//     }
//     return true;
// }

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
