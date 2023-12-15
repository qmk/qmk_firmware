/* Copyright 2020 dsanchezseco
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

#define ESC_CTL LCTL_T(KC_ESC)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _DVORAK,
    _DVORAK_NUM,
    _QWERTY,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_ortho_5x15( /* DVORAK */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,   KC_BSLS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MUTE,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_LBRC,  KC_PSCR, KC_RBRC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
        ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_HOME,  KC_MNXT, KC_PGUP, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_END,   KC_MPLY, KC_PGDN, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    SC_SENT,
        KC_LCTL, KC_LGUI, KC_LALT, _______, MO(_FN), KC_SPC,  KC_SPC,   KC_MPRV, KC_BSPC, KC_BSPC, MO(_FN), _______, KC_RALT, KC_RGUI, KC_RCTL
    ),
    [_DVORAK_NUM] = LAYOUT_ortho_5x15( /* DVORAK with center NUMPAD*/
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,   KC_BSLS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MUTE,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_P7,    KC_P8,   KC_P9, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
        ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_P4,    KC_P5,   KC_P6, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_P1,    KC_P2,   KC_P3, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    SC_SENT,
        KC_LCTL, KC_LGUI, KC_LALT, _______, MO(_FN), KC_SPC,  KC_SPC,   KC_P0,   KC_BSPC, KC_BSPC, MO(_FN), _______, KC_RALT, KC_RGUI, KC_RCTL
    ),

    [_QWERTY] = LAYOUT_ortho_5x15( /* QWERTY */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,   KC_BSLS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,  KC_PSCR, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH,
        ESC_CTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,  KC_MNXT, KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,   KC_MPLY, KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, SC_SENT,
        KC_LCTL, KC_LGUI, KC_LALT, _______, MO(_FN), KC_SPC,  KC_SPC,   KC_MPRV, KC_BSPC, KC_BSPC, MO(_FN), _______, KC_RALT, KC_RGUI, KC_RCTL
    ),

    [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   DF(_QWERTY), DF(_DVORAK_NUM), DF(_DVORAK), KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, _______, _______, _______, _______,
        _______, _______, _______, KC_DOWN, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, MO(_FN), _______, _______, KC_NUM,  KC_DEL,  KC_DEL,  MO(_FN), _______, _______, _______, _______
    )

};

bool led_update_user(led_t led_state) {
    // disable keyboard level handling
    return false;
}

void led_keypress_update(pin_t led_pin, uint16_t keycode, keyrecord_t *record) {
    // When a key is pressed turn on the LED, when released turn it off
    writePin(led_pin, record->event.pressed);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update LED state
    led_keypress_update(LED, keycode, record);
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Encoder on the LEFT */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Encoder on the RIGHT */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
