/* Copyright 2020 Steven Nguyen
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

enum framework_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _BOTH,
    _FN
};

enum framework_keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    BOTH,
    FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = framework_via(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,       KC_5,    KC_6,   KC_7,       KC_8,    KC_9,    KC_0,    KC_MEDIA_PLAY_PAUSE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,   KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,    KC_H,   KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_N,   KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), MO(_LOWER), KC_SPC,  KC_SPC, MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP
),

[_LOWER] = framework_via(
    _______, _______, _______, _______, _______, _______, _______, _______,   _______, KC_MINS, KC_EQL,  _______,
    KC_LEAD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______,   _______, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_DEL,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______,   _______, _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,   _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, MO(_BOTH), KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    C(S(KC_TAB)), C(KC_TAB)
),

[_RAISE] = framework_via(
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, MO(_BOTH), _______, _______, _______, _______, _______, _______, _______,
    C(KC_LEFT), C(KC_RIGHT)
),

[_BOTH] = framework_via(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EEP_RST, DEBUG,
    C(KC_Z), C(KC_Y)
),

[_FN] = framework_via(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_MS_WH_LEFT, KC_MS_WH_RIGHT
)
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // qq, alt+f4 close window
        SEQ_TWO_KEYS(KC_Q, KC_Q) {
            tap_code16(A(KC_F4));
        }

        // ee, open explorer
        SEQ_TWO_KEYS(KC_E, KC_E) {
            tap_code16(G(KC_E));
        }

        // rr, windows run prompt
        SEQ_TWO_KEYS(KC_R, KC_R) {
            tap_code16(G(KC_R));
        }

        // ww, maximize window
        SEQ_TWO_KEYS(KC_W, KC_W) {
            tap_code16(G(KC_UP));
        }

        // ss, minimize window
        SEQ_TWO_KEYS(KC_S, KC_S) {
            tap_code16(G(KC_DOWN));
        }

        // <space><space>, toggle desktop
        SEQ_TWO_KEYS(KC_SPC, KC_SPC) {
            tap_code16(G(KC_D));
        }
    }
} 

void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);
    if (index == 0) {
        if (clockwise) {
            tap_code16(dynamic_keymap_get_keycode(layer, 10, 1));
        } else {
            tap_code16(dynamic_keymap_get_keycode(layer, 10, 0));
        }
    }
}