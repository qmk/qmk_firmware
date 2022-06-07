/* Copyright 2017 Wunder
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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x15(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,         KC_5,   LGUI(KC_MINS), LGUI(KC_EQL),  KC_6,   KC_7,         KC_8,    KC_9,    KC_0,    LGUI(KC_0), KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,         KC_T,   LGUI(KC_LCBR), LGUI(KC_RCBR), KC_Y,   KC_U,         KC_I,    KC_O,    KC_P,    KC_GRV,     KC_BSLS,
        KC_PENT, KC_A,    KC_S,    KC_D,    KC_F,         KC_G,   LGUI(KC_LBRC), LGUI(KC_RBRC), KC_H,   KC_J,         KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,         KC_B,   LGUI(KC_QUES), LGUI(KC_SLSH), KC_N,   KC_M,         KC_COMM, KC_DOT,  KC_SLSH, KC_UP,      KC_RSFT,
        MO(2),  KC_LCTL, KC_LALT, KC_LGUI, LT(1,KC_SPC), KC_SPC,  KC_LSFT,       KC_RSFT,       KC_SPC, LT(1,KC_SPC), KC_RGUI, MO(2),   KC_LEFT, KC_DOWN,    KC_RGHT
        ),

    [1] = LAYOUT_ortho_5x15(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, LGUI(KC_0), LGUI(KC_0), KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,       KC_NO,         KC_DEL,
        KC_GRV,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,       KC_NO,         KC_NO,
        KC_GRV,  KC_TILD, KC_AT,   KC_PERC, KC_AMPR, KC_ASTR, KC_NO,      KC_NO,      KC_HASH, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN,       KC_NO,         KC_NO,
        KC_TRNS, KC_UNDS, KC_PLUS, KC_MINS, KC_EQL,  KC_EXLM, KC_NO,      KC_NO,      KC_CIRC, KC_DLR,  KC_QUES, KC_SLSH, KC_NO,         LCAG(KC_UP),   KC_TRNS,
        MO(3),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_TRNS, KC_TRNS, MO(3),  LGUI(KC_LBRC), LCAG(KC_DOWN), LGUI(KC_RBRC)
        ),

    [2] = LAYOUT_ortho_5x15(
        DB_TOGG,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  LGUI(KC_0), LGUI(KC_0), KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_NO,   KC_DEL,
        KC_NO,      KC_F11,  KC_F12,  KC_F13,  KC_F14, KC_F15, KC_NO,      KC_NO,      KC_F16, KC_F17, KC_F18,  KC_F19,  KC_F20,  KC_NO,   KC_NO,
        HYPR(KC_H), KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,  KC_NO,  KC_NO,      KC_NO,      KC_F21, KC_F22, KC_F23,  KC_F24,  KC_NO,   KC_NO,   KC_NO,
        KC_TRNS,    KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,  KC_NO,  KC_NO,      KC_NO,      KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, MO(3),  KC_NO,  KC_NO,      KC_NO,      KC_NO,  MO(3), KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
        ),

    [3] = LAYOUT_ortho_5x15(
        DB_TOGG,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   RGB_RMOD, RGB_MOD, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, QK_BOOT,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   RGB_HUD,  RGB_HUI, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   RGB_SAD,  RGB_SAI, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, DB_TOGG,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   RGB_VAD,  RGB_VAI, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, RGB_SPD, KC_NO,    KC_NO,   RGB_SPI, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO
        )
};


