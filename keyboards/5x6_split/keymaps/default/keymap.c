/* Copyright 2021 beanaccle
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
#include "keymap_swedish.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NUM,
    _SYM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
		KC_ESC,  SE_1,          SE_2,    SE_3,    SE_4,    SE_5,  SE_6,   SE_7,  SE_8,    SE_9,    SE_0,          SE_PLUS,
		KC_ESC,  SE_Q,          SE_W,    SE_F,    SE_P,    SE_G,  SE_J,   SE_L,  SE_U,    SE_Y,    SE_ODIA,       SE_ARNG,
		KC_BSPC, SE_A,          SE_R,    SE_S,    SE_T,    SE_D,  SE_H,   SE_N,  SE_E,    SE_I,    SE_O,          SE_ADIA,
		KC_LSFT, SE_Z,          SE_X,    SE_C,    SE_V,    SE_B,  SE_K,   SE_M,  SE_COMM, SE_DOT,  SE_MINS,       KC_LSFT,
		KC_LCTL, LCTL(KC_LSFT), KC_LGUI, KC_LALT, MO(1),      KC_SPC, KC_SPC,    MO(2), KC_ENT, KC_LGUI, LCTL(KC_LSFT), KC_LCTL
    ),
    [_NUM] = LAYOUT(
		KC_ESC,  SE_1,          SE_2,    SE_3,    SE_4,    SE_5,  SE_6,   SE_7,  SE_8,    SE_9,    SE_0,          SE_PLUS,
		KC_TAB,  SE_1,    SE_2,     SE_3,    SE_4,    SE_5,     SE_6,    SE_7,    SE_8,    SE_9,    SE_0,    SE_PLUS,
		KC_TRNS, KC_TRNS, KC_LEFT , KC_UP,   KC_DOWN, KC_RIGHT, KC_HOME, KC_END,  KC_PGDN, KC_PGUP, KC_TRNS, KC_F12,
		KC_TRNS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
		KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,      MO(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_SYM] = LAYOUT(
		KC_ESC,  SE_1,          SE_2,    SE_3,    SE_4,    SE_5,  SE_6,   SE_7,  SE_8,    SE_9,    SE_0,          SE_PLUS,
		KC_DEL,  SE_EXLM, SE_AT,   SE_DLR,  SE_TILD, SE_CIRC, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, SE_LABK, KC_TRNS,
		KC_TRNS, KC_TRNS, SE_DQUO, SE_HASH, SE_PERC, SE_QUOT, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL,  SE_RABK, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SE_ASTR, SE_BSLS, SE_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, SE_AMPR,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, SE_PIPE
    )
};
