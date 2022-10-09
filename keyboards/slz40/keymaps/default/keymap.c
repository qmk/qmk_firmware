/* Copyright 2020 SithLord
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
    _FN,
	_FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
		KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_SLSH, KC_BSPC,
		LT(_FN, KC_TAB),  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  LT(_FN,KC_ENT),
		KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_RSPC, 
		KC_LCTL, KC_LGUI, KC_LALT,  LT(_FN2, KC_DEL), LT(_FN2, KC_ENTER),   KC_SPACE,   KC_QUOT,  KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FN] = LAYOUT(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,  KC_SLSH, KC_BSPC,
		KC_TRNS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_PIPE,  KC_MINS,  KC_EQL,  KC_NO,  KC_BSLS,  KC_TRNS,
		KC_LSFT,   KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,  KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, KC_PGUP, KC_RSFT, 
		KC_LCTL, KC_LGUI, KC_LALT,  KC_TRNS, KC_TRNS,   KC_SPACE,   KC_QUOT,  KC_HOME, KC_PGDN, KC_END
    ),
    [_FN2] = LAYOUT(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, QK_BOOT,
		KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, KC_BSPC,
		KC_TAB,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BSLS,  KC_UNDS,  KC_PLUS,  KC_NO,  KC_NO,  KC_ENT,
		KC_LSFT,   KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_LCBR, KC_RCBR, KC_COMM, KC_DOT, KC_VOLU, KC_RSFT, 
		KC_LCTL, KC_LGUI, KC_LALT,  KC_TRNS, KC_TRNS,   KC_SPACE,   KC_QUOT,  KC_HOME, KC_VOLD, KC_END
    )
};
