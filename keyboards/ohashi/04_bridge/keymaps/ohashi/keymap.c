/* Copyright 2021 Ohashi
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

#define ___ _______

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _eucalyn,
    _qwerty,
    _qwe_N,
    _dvorak,
    _N,         //Number Layer
    _F,         //Functions and Brackets Layer
    _M,         //Marks Layer
    _C,         //Corsur Layer
    _MS,       //Mouse Controlling Layer
    _O,       //Others
    _NULL       //Empty Leyer for creating new one
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CTL_F11,
    MIA,
    ALT_GRAVE,
    QMKBEST = SAFE_RANGE,
    QMKURL
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_dvorak] = LAYOUT(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y,             KC_ESC,       KC_LGUI, KC_F, KC_G, KC_C, KC_R, KC_L,  LT(_O, KC_BSPC), 
        KC_LSFT, KC_A,    KC_O,    KC_E,   KC_U, KC_I,             KC_LALT,      KC_1,    KC_D, KC_H, KC_T, KC_N, KC_S,  KC_ENT, 
        KC_LCTL, KC_SCLN, KC_Q,    KC_J,   KC_K, LT(_qwe_N, KC_X), KC_SPC,       KC_3,    KC_B, KC_M, KC_W, KC_V, KC_Z,  KC_0
    ),
    [_qwe_N] = LAYOUT(
        KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    ___,       ___, ___, ___, ___, ___, ___, ___,
        KC_ENTER, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    ___,       ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___, ___,                               ___, ___, ___, ___, ___, ___, ___ 
    ),
    [_qwerty] = LAYOUT(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,             KC_ESC,       KC_LGUI, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    LT(_O, KC_BSPC), 
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_LALT,      KC_1,    KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENT, 
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, LT(_qwe_N, KC_B), KC_SPC,       KC_3,    KC_N, KC_M, KC_COMM, KC_DOT,KC_SLSH,  KC_0
    ),
    [_eucalyn] = LAYOUT(
        LT(_C, KC_TAB),   LCTL_T(KC_Q),  KC_W,         LSFT_T(KC_B), KC_F,         KC_COMM,        KC_DOT,                 KC_UP,  LT(_C,KC_M),    KC_R,        LT(_C, KC_D), KC_Y,  KC_P,   LT(_O, KC_BSPC),
        LCTL_T(KC_SCLN),  KC_A,          KC_O,         KC_E,         KC_U,         LT(_F,KC_I),    KC_F16,              KC_DOWN,  KC_G,           KC_T,        KC_K,         KC_N,  KC_S,   LCTL_T(KC_MINS),
        LT(_MS, KC_ESC),  KC_Z,          LGUI_T(KC_X), LALT_T(KC_C), LT(_M,KC_V),  LSFT_T(KC_SPC), KC_F15,               KC_ENT,  LT(_N,KC_ENT),  LT(_M,KC_H), LT(_F,KC_J),  KC_L,  KC_ENT, KC_1
    ),
    //number
    [_N] = LAYOUT(
        _______, KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH,       KC_EQL, _______,       _______, KC_EQL,  KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,          KC_5,   _______,        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, _______, _______, _______,LALT(KC_GRAVE), KC_F15, _______,         _______, KC_F16, _______, _______, _______, _______, _______
    ),
    //Functions and Brackets
    [_F] = LAYOUT(
        _______, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, _______, _______,          _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
        _______, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, _______, _______,          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_EXLM, KC_QUES, KC_AMPR, KC_PIPE, _______, _______,          _______, KC_F11,   KC_F12,  _______, _______, _______, _______ 
    ),
    //marks
    [_M] = LAYOUT(
        KC_BSLS,  KC_QUES, KC_EXLM, KC_SLSH, KC_DOT,  KC_COMM, _______,        _______, _______, _______, _______, _______, _______, KC_DEL, 
        KC_GRAVE, KC_QUOT, KC_DQUO, KC_UNDS, KC_MINS, KC_TILD, _______,        _______, KC_HOME, KC_END,  _______, _______, _______, _______,
        _______,  _______, _______, _______, KC_F15,  _______, _______,        _______, _______,  KC_F16, _______, _______, _______, _______
    ),  
    //cursor
    [_C] = LAYOUT(
        _______, _______, KC_BSPC, KC_UP,   KC_DEL,   _______, _______,       _______, _______, _______, _______, _______, _______, _______, 
        KC_PGUP, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  _______,       _______, _______, _______, _______, _______, _______, _______,
        KC_PGDN, _______, _______, _______, _______,  _______, _______,       _______, _______, _______, _______, _______, _______, _______
    ),
    //mouse1
    [_MS] = LAYOUT(
        KC_WH_U, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        KC_WH_D, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        _______, KC_WH_L, KC_WH_R, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______
    ),
    //O
    [_O] = LAYOUT(
        TO(_eucalyn),  TO(_qwerty), TO(_dvorak),  _______, _______, _______, _______,        _______, _______, KC_INT4, KC_INT5, KC_BRID, KC_BRIU, _______,     
        _______,       _______,     _______,      _______, _______, _______, _______,        _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUSE, 
        _______,       _______,     _______,      _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, KC_CAPS 
    ),
    //Null
    [_NULL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_F11:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                register_code(KC_LCTL);
                tap_code(KC_F11);
                unregister_code(KC_LCTL);
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case MIA:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                register_code(KC_LCTL);
                tap_code(KC_F12);
                unregister_code(KC_LCTL);
            } else {
                // when keycode QMKBEST is released
            }
            break;
         case ALT_GRAVE:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                register_code(KC_LALT);
                tap_code(KC_GRAVE);
                unregister_code(KC_LALT);
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
