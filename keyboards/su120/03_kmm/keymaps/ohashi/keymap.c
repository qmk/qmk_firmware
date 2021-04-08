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
    [_qwerty] = LAYOUT(
        
                 KC_Q,  KC_W, KC_E, KC_R, KC_T,                        KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_LSFT, KC_A,  KC_S, KC_D, KC_F, KC_G, KC_0,            KC_1, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_MINS, 
                        KC_X, KC_C, KC_V, KC_B, KC_2,            KC_3, KC_N, KC_M, KC_COMM, KC_UP,
                            KC_LGUI,KC_LALT, KC_ESC, KC_SPC,   KC_ENT, KC_LEFT, KC_RIGHT, KC_DOWN
    ),
    /*[_qwe_N] = LAYOUT(
        KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,        _______, _______, _______, _______, _______, _______, 
        KC_ENTER, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,        _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, KC_LALT, KC_ESC,  _______,     _______, _______, _______, _______, _______, _______, 
                                            _______, _______,      _______, _______
        ,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    */[_eucalyn] = LAYOUT(
                          LT(_O, KC_Q), KC_W,         KC_B,           KC_F,   KC_Z,                             LT(_C,KC_M), KC_R,  LT(_C, KC_D),  LT(_O, KC_Y), LT(_MS, KC_P), 
        LCTL_T(KC_ESC),   KC_A,         KC_O,         KC_E,           KC_U,   KC_I,          KC_LGUI,       KC_UP, KC_G,        KC_T,  KC_K,         KC_N,         KC_S,            KC_MINS,
                                        LSFT_T(KC_X), LALT_T(KC_C),   KC_V,   LCTL_T(KC_TAB),  KC_SCLN,        KC_DOWN, KC_BSPC,     KC_H,  KC_J,         KC_L,          
                                              KC_ESC,LT(_M, _______),LT(_N, KC_SPC), SFT_T(KC_F15),         LT(_F, KC_F16),LT(_N, KC_ENTER), LT(_M, KC_LEFT),    KC_RIGHT
    ),
    //number
    [_N] = LAYOUT(
                    _______, _______,_______, _______,_______,         _______,_______, _______,_______, _______,
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, _______ ,               _______, KC_6, KC_7, KC_8, KC_9, KC_0,         _______,
                KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, KC_EQL,            KC_EQL,  KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, 
                                    ___, ___, ___, ___,                ___, ___, ___, ___
    ),
    //Functions and Brackets
    [_F] = LAYOUT(
                KC_F2, KC_F3, KC_F4, KC_F5,        KC_F6,                    KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
        KC_F1, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN,    ___, ___,   KC_CIRC, KC_DLR,  KC_AMPR, KC_PIPE,  KC_F12,
                 ___,      ___,     ___,     ___,     ___,               ___, ___,   ___,   ___,   ___, 
                                 ___,     ___,     ___,     ___,        ___,     ___,     ___,     ___
    ),
    //marks
    [_M] = LAYOUT(
                 KC_GRAVE,KC_BSLS, _______, _______, _______,                          _______, _______, _______, _______, _______, 
        _______, KC_DOT,  KC_COMM, KC_UNDS, KC_MINS, KC_TILD, _______,        _______, KC_HOME, KC_END,  _______, _______, _______, _______,
                          KC_EXLM, KC_QUES, KC_DQUO, KC_QUOT, _______,        _______, KC_DEL,  _______, _______, _______,
        _______, _______, _______, _______,                                   _______,_______,_______,_______
    ),  
    //cursor
    [_C] = LAYOUT(
                 _______, KC_BSPC, KC_UP,   KC_DEL,   _______,                          _______, _______, _______, _______, _______, 
        _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  _______,        _______, _______, _______, _______, _______,  _______, _______,
                          _______, KC_PGUP, _______,  _______,  _______,                          _______, _______, _______,  _______,  _______, 
                                   KC_PGDN, _______, _______, _______,                                    _______, _______, _______, _______
    )/*,
    //mouse1
    [_MS] = LAYOUT(
        _______, _______, _______, _______, _______,               _______, KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1, _______, 
        _______, KC_MS_BTN1, KC_MS_U, KC_MS_BTN1, KC_MS_BTN2,      _______, _______, _______, _______, _______, 
        KC_WH_U, KC_MS_L,    KC_MS_D, KC_MS_R,    KC_WH_U,         _______, KC_WHOM, KC_WREF, _______, _______, 
        KC_WH_D, _______,    _______, _______,    KC_WH_D,         _______, _______, _______, _______, _______,
        _______, KC_WH_L, KC_WH_R,    _______,                              _______, _______, _______, _______
    ),
    //O
    [_O] = LAYOUT(
        TO(_eucalyn),  TO(_qwerty), _______, _______, _______,      KC_INT4, KC_INT5, KC_BRID, KC_BRIU, _______,     
        _______, LCTL(KC_W), LSFT(KC_TAB), KC_ENT,  _______,               _______, _______, KC_PSCR, KC_SLCK, KC_PAUSE, 
        KC_ESC,  LCTL(KC_S), KC_TAB, KC_UP,   _______,              _______, LCTL(KC_T), KC_INS, KC_HOME, KC_PGUP, 
        _______, _______, _______, KC_DOWN, _______, _______, _______,  KC_DEL,  KC_END,  KC_PGDN,  
        _______, _______, KC_LCTL, KC_LALT,                                 _______, _______, _______, KC_CAPS
    ),
    //Null
    [_NULL] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______
        ,_______,_______,_______,_______,_______,_______,_______,_______
    )*/
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
