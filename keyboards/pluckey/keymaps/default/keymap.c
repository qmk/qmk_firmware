/* Copyright 2021 floookay
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
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    M_ARROW
};

#define MO_LOW MO(_LOWER)
#define MO_RAIS MO(_RAISE)
#define MO_ADJU MO(_ADJUST)
#define MO_CURR _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,                        KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                        KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LPRN,                        KC_RPRN, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR, KC_HOME,      KC_END,  KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, MO_LOW,      KC_SPC,    KC_BSPC,            KC_ENT,    KC_SPC,      MO_RAIS, KC_RALT, KC_MEH
    ),
    [_LOWER] = LAYOUT_all(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,                         KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
        _______, _______, _______, _______, KC_PIPE, KC_UNDS, KC_LPRN,                        KC_RPRN, KC_PLUS, KC_PIPE, _______, _______, _______, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LPRN,                        KC_RPRN, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, _______, M_ARROW, KC_PGUP,      KC_PGDN, _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, MO_CURR,     _______,   KC_DEL,             _______,   _______,     MO_ADJU, _______, _______
    ),
    [_RAISE] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, KC_PGUP, _______, _______, _______,
        _______, _______, _______, KC_VOLU, _______, _______, KC_LPRN,                        KC_RPRN, _______, KC_BTN4, KC_UP,   KC_BTN5, _______, _______,
        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_LPRN,                        KC_RPRN, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,
        _______, _______, _______, KC_VOLD, _______, _______, M_ARROW, KC_PGUP,      KC_PGDN, _______, _______, _______, KC_PGDN, _______, _______, _______,
                          _______, _______, MO_ADJU,     _______,   KC_DEL,             _______,   _______,     MO_CURR, _______, _______
    ),
    [_ADJUST] = LAYOUT_all(
        KC_SLEP, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, KC_WH_U, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______,     _______,   KC_CLR,            _______,   _______,     _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;
    }
    return true;
}
