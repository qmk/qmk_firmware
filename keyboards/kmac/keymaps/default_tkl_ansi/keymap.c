/* Copyright 2017-2019 Mathias Andersson <wraul@dbox.se>
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
    _QW,
    _FN,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MCR_01 = SAFE_RANGE,
    MCR_02,
    MCR_03,
    MCR_04,
    MCR_05,
    MCR_06,
    MCR_07,
    MCR_08,
    MCR_09,
    MCR_10,
    MCR_11,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_BRK,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [_FN] = LAYOUT_tkl_ansi(
        BL_STEP,          MCR_01,  MCR_02,  MCR_03,  MCR_03,  MCR_04,  MCR_05,  MCR_06,  MCR_07,  MCR_08,  MCR_09,  MCR_10,  MCR_11,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                   _______,                                     _______, _______, _______, _______, _______, _______, _______),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MCR_01:
            if (record->event.pressed) {
                SEND_STRING("The");
            }
            break;
        case MCR_02:
            if (record->event.pressed) {
                SEND_STRING("Custom");
            }
            break;
        case MCR_03:
            if (record->event.pressed) {
                SEND_STRING("Keyboard");
            }
            break;
        case MCR_04:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("c") SS_TAP(X_RIGHT) SS_LCTRL("v"));
            }
            break;
    }
    return true;
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
