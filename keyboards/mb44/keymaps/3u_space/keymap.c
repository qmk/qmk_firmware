/* Copyright 2020 melonbred
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LAYER1,
    _LAYER2,
    _LAYER3

};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_3u_space(
        KC_ESC,        KC_Q,    KC_W,    KC_E,                KC_R, KC_T, KC_Y,   KC_U,        KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_T(KC_TAB), KC_A,    KC_S,    KC_D,                KC_F, KC_G, KC_H,   KC_J,        KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,       KC_Z,    KC_X,    KC_C,                KC_V, KC_B, KC_N,   KC_M,        KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
        MO(_LAYER2),   KC_LGUI, KC_LALT, LT(_LAYER1, KC_SPC),             LT(_LAYER3, KC_SPC),          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LAYER1] = LAYOUT_3u_space(
        KC_GRV,  KC_QUOT, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8, KC_9,    KC_DEL,
        KC_CAPS, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_PSLS, KC_PMNS, KC_4, KC_5, KC_6,    KC_ENT,
        KC_LSFT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_PAST, KC_PPLS, KC_1, KC_2, KC_3,    KC_RSFT,
        XXXXXXX, KC_LGUI, KC_LALT, _______,                   XXXXXXX,                KC_0, KC_PDOT, KC_PEQL
    ),

    [_LAYER2] = LAYOUT_3u_space(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, KC_RCTL, KC_RALT, KC_DEL,  KC_VOLD,
        XXXXXXX, _______, XXXXXXX, XXXXXXX,                   XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_LAYER3] = LAYOUT_3u_space(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   _______,
        _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX,                   _______,                   XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

// Rotary Encoder Functions
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}