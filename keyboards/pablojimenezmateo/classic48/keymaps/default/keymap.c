/* Copyright 2025 Pablo Jiménez Mateo (@pablojimenezmateo)
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
    _MAIN,
    _NUMBERS,
    _SYMBOLS,
    _NAVIGATION
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_NO,      KC_Q,       KC_W,       KC_E,  KC_R,         KC_T,               KC_Y,            KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_TAB,     KC_A,       KC_S,       KC_D,  KC_F,         KC_G,               KC_H,            KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_ESCAPE,  KC_Z,       KC_X,       KC_C,  KC_V,         KC_B,               KC_N,            KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
        LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, MO(_NUMBERS), LT(3, KC_SPC),      LT(2, KC_ENTER), KC_LSFT, KC_NO,   KC_LGUI, KC_NO,   LCTL(KC_F)
    ),
    [_NUMBERS] = LAYOUT(
        KC_NO, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,      KC_NO, KC_7,  KC_8,  KC_9,  KC_NO, KC_NO,
        KC_NO, KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_NO,      KC_NO, KC_4,  KC_5,  KC_6,  KC_NO, KC_NO,
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,      KC_NO, KC_1,  KC_2,  KC_3,  KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_0,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [_SYMBOLS] = LAYOUT(
        KC_NO, KC_PIPE, KC_AT,   KC_LCBR, KC_RCBR, KC_CIRC,      KC_QUOT, KC_DQUO, KC_EQL,  KC_AMPR, KC_ASTR, KC_GRV,
        KC_NO, KC_EXLM, KC_EXLM, KC_LPRN, KC_RPRN, KC_DLR,       KC_EXLM, KC_QUES, KC_SLSH, KC_COLN, KC_SCLN, KC_PLUS,
        KC_NO, KC_HASH, KC_PERC, KC_LBRC, KC_RBRC, KC_TILD,      KC_LT,   KC_GT,   KC_MINS, KC_UNDS, KC_BSLS, KC_PSCR,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSPC,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT
    ),
    [_NAVIGATION] = LAYOUT(
        KC_NO,       KC_NO,      MS_BTN4,    MS_UP,   MS_BTN5, KC_NO,             LSFT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP),   LSFT(KC_RGHT), KC_NO,  KC_VOLU,
        KC_NO,       KC_NO,      MS_LEFT,    MS_DOWN, MS_RGHT, KC_LEFT_CTRL,      KC_HOME,       MS_BTN1,       MS_BTN3,       MS_BTN2,       KC_END, KC_VOLD,
        KC_NO,       KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,             KC_LEFT,       KC_DOWN,       KC_UP,         KC_RGHT,       KC_NO,  KC_BRIU,
        LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), KC_NO,   KC_NO,   KC_NO,             MS_WHLD,       MS_WHLU,       KC_NO,         KC_NO,         KC_NO,  KC_BRID
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _MAIN:
            /* Yellow */
            rgb_matrix_sethsv_noeeprom(50, 255, 255); break;   
        case _NUMBERS:
            /* Cyan */
            rgb_matrix_sethsv_noeeprom(170, 255, 255); break;
        case _SYMBOLS:
            /* Purple */
            rgb_matrix_sethsv_noeeprom(200, 255, 255); break;
        case _NAVIGATION:
            /* Green */
            rgb_matrix_sethsv_noeeprom(85, 255, 255); break;
        default:
            /* Off */
            rgb_matrix_sethsv_noeeprom(0, 0, 0); break;
    }
    return state;
}
