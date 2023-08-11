/* Copyright 2021 takashicompany
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    RADIALEX = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_ESC, KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, RADIALEX, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, KC_ENT,
        KC_LSFT, LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, KC_DEL,
        KC_PSCR, KC_LCTL, KC_LGUI, LALT_T(KC_LNG2), LSFT_T(KC_TAB), LT(2, KC_SPC), LT(1, KC_LNG1), KC_RALT, KC_RGUI, KC_RCTL 
    ),
    
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_TRNS, LCTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_INT1, KC_TRNS, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_INT3, KC_TRNS,
        KC_TRNS, LSFT_T(KC_PLUS), KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, LGUI(KC_INT3),
        KC_TRNS, KC_TRNS, KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_TRNS, KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LGUI, KC_LALT, KC_LNG2, KC_LSFT, KC_SPC, KC_LNG1, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_TRNS, KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, RADIALEX, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, KC_TRNS,
        KC_TRNS, LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, KC_TRNS,
        KC_PSCR, KC_LCTL, KC_LGUI, LALT_T(KC_LNG2), LSFT_T(KC_TAB), LT(5, KC_SPC), LT(4, KC_LNG1), KC_RALT, KC_RGUI, KC_RCTL 
    ),
        
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_TRNS, KC_CIRC, KC_AT, KC_SLSH, KC_MINS, KC_UNDS, KC_TRNS, KC_SCLN, KC_COLN, KC_LBRC, KC_RBRC, KC_INT3, KC_TRNS,
        KC_TRNS, LT(5, KC_TILD), KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR, KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_BSLS, 
        KC_TRNS, KC_TILD, KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_TRNS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
        KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_LSFT, KC_SPC, KC_LNG1, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, 
        KC_TRNS, KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_TRNS, 
        KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_TRNS, KC_NO, KC_LNG1, KC_NO, KC_NO, KC_DEL, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ), 
    
    LAYOUT(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_TRNS, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_TRNS, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(8), MO(9), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, DF(0), DF(3), 
        KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RADIALEX:
            if (record->event.pressed) {
                SEND_STRING("Radialex");
                rgblight_toggle();
            }
            return false;
    }
    return true;
}
