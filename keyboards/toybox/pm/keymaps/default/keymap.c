/* Copyright 2020 sekigon-gonnoc
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
#include "keycode.h"
#include QMK_KEYBOARD_H

#include "mtch6102.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KC = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
                 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, LALT(KC_GRV), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_RBRC, KC_BSLS,
                 LCTL_T(KC_TAB), KC_A, KC_S, KC_D, LSFT_T(KC_F), KC_G, KC_RCTL, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
                 KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_RSFT, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), RSFT_T(KC_RO), KC_UP,
                 KC_LGUI, KC_LALT, LT(1, KC_SPC), LT(1, KC_SPC), LT(2, KC_ENT), LT(2, KC_ENT), KC_DEL, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_TRNS, KC_LCBR, KC_MINS, KC_EQL, KC_RCBR, KC_COLN, KC_DQUO, KC_TRNS,
                 KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_RO, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_PAUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, KC_QUOT, KC_TRNS,
                 KC_TRNS, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_BTN1...KC_BTN5:
            if (record->event.pressed) {
                pointing_device_set_button(1 << (keycode - KC_BTN1));
            } else {
                pointing_device_clear_button(1 << (keycode - KC_BTN1));
            }
            return false;
            break;
    }

    return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
