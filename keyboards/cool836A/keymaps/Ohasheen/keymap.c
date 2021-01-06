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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _Ohasheen,
    _N,         //Mumbers Layer
    _F,         //Function Keys Layer
    _C,         //Corsur Layer
    _M,         //Marks Layer
    _MS1,       //Mouse Controlling Layer
    _NULL       //Empty Leyer for creating new one
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Ohasheen] = LAYOUT(
        LT(_C, KC_TAB), KC_Q,           KC_W,        KC_COMM,     KC_DOT,        KC_B,  \
        KC_LCTL,        KC_A,          KC_O,        KC_E,         LT(_C, KC_U), KC_I, \
        LSFT_T(KC_ESC), LT(_MS1, KC_Z), GUI_T(KC_X), LALT_T(KC_C), LT(_N, KC_V), LSFT_T(KC_SPC), \

                         KC_M,   KC_R,          KC_D, KC_Y, KC_P, LT(_MS1, KC_BSPC), \
                         KC_G,   LT(_C, KC_T),  KC_K, KC_N, KC_S, KC_MINS, \
        LT(_F, KC_ENTER), LT(_M, KC_F),         KC_H, KC_J, KC_L, LT(_C, KC_ENT)
    ),
    //number
    [_N] = LAYOUT(
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,\
        _______,  KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC,  KC_SCLN,\
        _______,  KC_LCBR, KC_RCBR, KC_DQUO, _______, KC_QUOT, \

        KC_6,    KC_7,     KC_8,    KC_9,    KC_0,   KC_DEL,\
        KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, KC_EQL,  _______,\
        _______, _______, _______, _______, _______, _______
    ),
    //function
    [_F] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,\
        _______, KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,\
        _______, KC_F11,  KC_F12, KC_CIRC, KC_TILD, _______,\

        _______, _______, _______, _______, _______,   KC_DEL,\
        KC_MUTE, KC_HOME, KC_END,  KC_PGUP, KC_PGDOWN, _______, \
        _______, _______, _______, _______, _______,   RESET 
    ),
    //Mark
    [_M] = LAYOUT(
        KC_GRAVE, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC, \
        _______,  KC_CIRC,  KC_DLR, KC_BSLS, KC_AMPR, KC_PIPE, \
        _______,  _______, _______, _______, _______, _______, \
        
        _______, KC_COLN, KC_ASTR, KC_SLSH, KC_TILD, KC_DEL, \
        KC_UNDS, KC_SCLN, KC_EXLM, KC_QUES, KC_EQL,  _______,\
        KC_MPLY, _______, KC_VOLD, KC_VOLU, KC_MPRV,   KC_MNXT
    ),  
    //cursor
    [_C] = LAYOUT(
        _______, KC_PSCR, KC_INS,  _______, _______, _______, \
        _______, _______, _______, _______, KC_INT5, _______,\
        _______, _______, _______, _______, KC_INT5, _______,\

        _______, _______, _______, KC_SLEP, _______,  KC_PWR ,\
        _______, KC_INT4, KC_UP,   KC_WBAK, KC_WFWD,  _______,\
        RESET,   KC_INT4, KC_LEFT, KC_DOWN, KC_RIGHT, _______
    ),
    //mouse1
    [_MS1] = LAYOUT(
        _______, _______, KC_MS_BTN1, KC_MS_U, KC_MS_BTN1, KC_MS_BTN2, \
        KC_WH_U, _______, KC_MS_L,    KC_MS_D, KC_MS_R,    _______, \
        KC_WH_D, _______, KC_WH_L,    KC_WH_R, _______,    KC_ACL1, \
        
        _______, _______, KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1, _______, \
        _______, KC_WHOM, _______,    KC_MS_BTN4, KC_MS_BTN5, _______, \
        _______, _______, _______,     _______,    KC_ACL1,   _______
    ),
    //Null
    [_NULL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
