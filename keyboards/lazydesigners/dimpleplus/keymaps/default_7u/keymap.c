/* Copyright 2020 LAZYDESIGNERS
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
    [0] = LAYOUT_7u(
        KC_ESC,    KC_1,    KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
        KC_GRV,    KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_BSPC,
        KC_TAB,    KC_A,    KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,                KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_RSFT,
        KC_LCTL,            KC_LGUI,                      KC_SPC,             KC_RALT,  MO(1)
    ),
    [1] = LAYOUT_7u(
        QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
        KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,   KC_DEL,
        KC_TAB,   KC_UNDS,  KC_SCLN,  KC_BSLS,  KC_QUOT,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_UP,               KC_SLSH,
        KC_LSFT,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_MSTP,  KC_MPLY,  KC_MFFD,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_RSFT,
        KC_CAPS,            MO(2),                        KC_SPC,             KC_NO,    KC_TRNS
    ),
    [2] = LAYOUT_7u(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_RMOD, RGB_MOD,  RGB_VAD,  RGB_VAI,  RGB_SPD,  RGB_SPI,  KC_TRNS,             KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_TOG,  RGB_HUD,  RGB_HUI,  RGB_SAD,  RGB_SAI,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,            KC_TRNS,                      KC_TRNS,            KC_TRNS,  KC_TRNS
    )
};
