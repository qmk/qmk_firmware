/* Copyright 2020 Tvrd Rad Keyboards
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
    _FN
};

// RGB_TOG - On off led

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,      KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,      KC_7,    KC_8,     KC_9,    KC_0,          KC_MINUS,    KC_EQUAL,  KC_KP_SLASH, KC_KP_ASTERISK,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,      KC_U,    KC_I,     KC_O,    KC_P,          KC_LBRACKET, KC_RBRC,   KC_BSLASH,   KC_HOME,
        KC_CAPSLOCK, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,      KC_J,    KC_K,     KC_L,    KC_AUDIO_MUTE, KC_SCOLON,   KC_QUOTE,  KC_ENTER,    KC_END,
        KC_LSHIFT,   KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,      KC_M,    KC_COMMA, KC_DOT,  _______,       KC_SLASH,    KC_RSHIFT, KC_UP,       KC_DELETE,
        KC_LCTRL,    KC_LGUI, KC_LALT, _______, KC_SPACE, _______, KC_BSPACE, _______, MO(_FN),  _______, _______,       KC_RCTRL,    KC_LEFT,   KC_DOWN,     KC_RIGHT
    ),
    [_FN] = LAYOUT(
        RESET,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_KP_MINUS, KC_KP_PLUS,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_PGUP,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_PGDOWN,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_DOWN);
        } else {
            tap_code(KC_AUDIO_VOL_UP);
        }
    }
    return false;
}
