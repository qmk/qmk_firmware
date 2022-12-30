/*
 * Copyright 2022 M. Adam Price
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "version.h"

enum custom_keycodes {
    VER_STR = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VER_STR:
            if (record->event.pressed) {
                SEND_STRING("# qmk " QMK_VERSION "\n");
                wait_ms(VER_NEWLINE_WAIT);
                SEND_STRING("# " QMK_KEYBOARD "/" QMK_KEYMAP " version " KEYMAP_REVISION "\n");
                wait_ms(VER_NEWLINE_WAIT);
                SEND_STRING("# built on: " QMK_BUILDDATE "\n");
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_1x2uC(
            KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
            XXXXXXX,        KC_ALGR, KC_LGUI, KC_LALT, MO(1),   KC_SPC,           MO(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [1] = LAYOUT_planck_1x2uC(
            KC_GRV,         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
            _______,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
            _______,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
            KC_INS,         _______, _______, _______, _______, _______,          MO(3),   KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [2] = LAYOUT_planck_1x2uC(
            KC_TILD,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
            _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            _______,        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            KC_INS,         _______, _______, _______, MO(3),   _______,          _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [3] = LAYOUT_planck_1x2uC(
            QK_BOOT,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_DEL,
            XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
            KC_CAPS,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, VER_STR,
            _______,        XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
