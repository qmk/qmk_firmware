/* Copyright 2021 Regan Palmer
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

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY, KC_PSCR, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPC,
		KC_LCTL, KC_LALT, KC_LGUI, RAISE , KC_LSFT, KC_SPC, LOWER, KC_RGUI, KC_RALT, KC_RCTL
		),

	[_LOWER] = LAYOUT(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
		KC_TILD, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_LCBR, KC_RCBR, KC_COLN, KC_DQT, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_PIPE, KC_UNDS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ADJUST, KC_TRNS, KC_TRNS
		),

	[_RAISE] = LAYOUT(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
		KC_ESC, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_TRNS,
		KC_TAB, KC_CAPS, KC_DELETE, KC_SLASH, KC_MINUS, KC_TRNS, KC_TRNS, KC_PLUS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI, KC_TRNS, KC_TRNS
		),

    [_ADJUST] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY, KC_PSCR, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPC,
		KC_LCTL, KC_LALT, ADJUST, RAISE, KC_SPC, KC_LSFT, LOWER, ADJUST, KC_RALT, KC_RCTL
		),
};


bool encoder_update_user(uint8_t index, bool clockwise) {


	switch (get_highest_layer(layer_state)) {
        case _BASE:
             if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
            break;
        case _RAISE:
            if (index == 0) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_WH_R);
        } else {
            tap_code(KC_WH_L);
        }
    }
            break;
		case _LOWER:
			if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_END);
        } else {
            tap_code(KC_HOME);
        }
    }
			break;
        case _ADJUST:
             if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_RIGHT);
        } else {
            tap_code(KC_MS_LEFT);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_DOWN);
        } else {
            tap_code(KC_MS_UP);
        }
    }
            break;
    }
    return true;
}
