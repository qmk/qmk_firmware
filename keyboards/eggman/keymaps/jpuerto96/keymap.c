/* Copyright 2020 qpockets
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

enum layers{
  _BASE,
  _LOWER,
  _RAISE
};

// Left-hand HR Mods
#define ALT_A ALT_T(KC_A)
#define GUI_S GUI_T(KC_S)
#define SFT_D SFT_T(KC_D)
#define CTL_F CTL_T(KC_F)

// Right-hand HR Mods
#define CTL_J  CTL_T(KC_J)
#define SFT_K  SFT_T(KC_K)
#define GUI_L  GUI_T(KC_L)
#define ALT_SC ALT_T(KC_SCLN)

#define ____ KC_TRNS

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_default(
									KC_LGUI,	  KC_MPLY,
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_ESC,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
    ALT_A,  GUI_S,  SFT_D,  CTL_F,   KC_G,  KC_TAB,  KC_H,   CTL_J,  SFT_K,    GUI_L, ALT_SC,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_BSPC,  KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                              LOWER,  KC_SPC,    KC_ENT, RAISE
  ),

 [_LOWER] = LAYOUT_default(
								    KC_TRNS,     KC_TRNS,
    KC_1,  KC_2,    KC_3,   KC_4,   KC_5,    ____,    KC_6,   KC_7,    KC_8,    KC_9,  KC_0,
    KC_PIPE, KC_GRV, KC_TILD, ____, ____,    ____,    ____,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
    ____,  ____,    ____,   ____,   ____,    ____,    ____,   ____,     ____,   ____,  ____,
                             ____,    ____,       ____,   ____
  ),

  [_RAISE] = LAYOUT_default(
 									KC_TRNS,        KC_TRNS,
    KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC, RESET, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F1,   KC_F2, KC_F3,   KC_F4,  KC_F5,    ____,  KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_QUOT,
    KC_F6,   KC_F7, KC_F8,   KC_F9,  KC_F10,   ____,  KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
                             ____,    ____,       ____, ____
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

