/* Copyright 2021 Alan Lehners
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
  _SYM,
  _NAV
};

enum combo_events {
 COMBO_BSPC,
 COMBO_ENT,
 COMBO_TAB,
 COMBO_ESC,
 COMBO_DEL
};
#define KC_DN_BSPC LT(_NAV, KC_BSPC)
#define KC_UP_SPC LT(_SYM, KC_SPC)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_default(
									KC_LGUI,	  KC_MPLY,
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_DEL,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
    KC_A,   KC_S,   KC_D,  KC_SF,   KC_G,   KC_TAB,  KC_H,   KC_SJ,  KC_K,    KC_L,   KC_QUOT,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,  KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                  KC_LCTL,  KC_DN_BSPC,    KC_UP_SPC, KC_RALT
  ),

 [_SYM] = LAYOUT_default(
										KC_TRNS,        KC_TRNS,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS,
    KC_PIPE, KC_BSLS, KC_LPRN, KC_LBRC, KC_SCLN, KC_TRNS, KC_COLN, KC_RBRC, KC_RPRN, KC_PLUS,  KC_UNDS,
                    KC_TRNS,   KC_TRNS,    KC_TRNS,      KC_TRNS
  ),

  [_NAV] = LAYOUT_default(
 										KC_TRNS,        KC_TRNS,
    KC_TRNS, KC_HOME, KC_UP,   KC_END,   KC_PGUP,  QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TAB,
    KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT,  KC_TRNS,  KC_LCAP, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_ENT,
                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* left encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) { /* right encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_ENT] = COMBO(combo_ent,KC_ENT),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL)
};
#endif
