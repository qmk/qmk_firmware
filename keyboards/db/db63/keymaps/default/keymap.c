/*
Copyright 2020 Hung DO <hungdohuy@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

uint8_t current_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        MO(3),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,   MO(2),
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_SLSH, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_GRV, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DM_PLY1, DM_PLY2, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          _______,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_PGUP,   XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    _______, MO(1),   KC_HOME, KC_PGDOWN, KC_END
    ),
    [2] = LAYOUT(
        KC_GESC, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_TOG, RGB_VAD, RGB_VAI, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DM_REC1, DM_REC2, KC_BSLS,
        XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          DM_RSTP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,   MO(2),
        KC_LCTL, KC_LALT, KC_LGUI,                              KC_SPC,                    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, BL_BRTG, BL_TOGG, BL_DEC,  BL_INC,  _______,
        KC_TAB,  KC_Q,    KC_UP,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    S(KC_INS),    KC_O,    KC_P,    _______, _______, KC_BSLS,
        MO(3),   KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  RESET,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    S(KC_INS),    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_VOLU,   XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    _______, XXXXXXX, KC_MRWD, KC_VOLD, KC_MFFD
    ),
};

void dynamic_macro_record_start_user(void) {
    current_mode = rgblight_get_mode();
    rgblight_mode(16);
}

void dynamic_macro_record_end_user(int8_t direction) {
    rgblight_mode(current_mode);
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_sethsv(HSV_CYAN);
        writePinHigh(D1);
    } else {
        rgblight_sethsv(HSV_GREEN);
        writePinLow(D1);
    }
    return false;
}
