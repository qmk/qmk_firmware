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
[_BASE] = LAYOUT_ortho_5x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MEDIA_PLAY_PAUSE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, FN,      LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_LOWER] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______,
    KC_LEAD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_DEL,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______,
    KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______, _______, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

[_RAISE] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_TRNS, _______, _______, KC_TRNS, _______, _______, _______, _______
),

[_BOTH] = LAYOUT_ortho_5x12(
    _______, _______,     _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    _______, LALT(KC_F4), _______, KC_MYCM, LGUI(KC_R), _______, _______, _______, _______, _______, _______, _______,
    _______, _______,     _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    _______, _______,     _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    _______, _______,     _______, _______, _______,    _______, _______, _______, _______, _______, _______, DEBUG
),

[_FN] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                if (clockwise) {
                    tap_code(KC_AUDIO_VOL_UP);
                } else {
                    tap_code(KC_AUDIO_VOL_DOWN);
                }
                break;

            case _LOWER:
                if (clockwise) {
                    tap_code16(LCTL(KC_TAB));
                } else {
                    tap_code16(LCTL(LSFT(KC_TAB)));
                }
                break;

            case _RAISE:
                if (clockwise) {
                    tap_code16(LCTL(KC_RGHT));
                } else {
                    tap_code16(LCTL(KC_LEFT));
                }
                break;

            case _BOTH:
                if (clockwise) {
                    tap_code16(LCTL(KC_Y));
                } else {
                    tap_code16(LCTL(KC_Z));
                }
                break;

            case _FN:
                if (clockwise) {
                    tap_code(_______);
                } else {
                    tap_code(_______);
                }
                break;

            default:
                break;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            }
            return false;

        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            }
            return false;

        case FN:
            if (record->event.pressed) {
                layer_on(_FN);
            } else {
                layer_off(_FN);
            }
            return false;
    }
    return true;
}
