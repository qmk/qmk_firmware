/* Copyright 2019 gtips
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
#include "keymap_japanese.h"

enum layer_names {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)

#define CT_Q  LCTL_T(JP_Q)
#define CT_CM RCTL_T(JP_COMM)
#define SF_Z  LSFT_T(JP_Z)
#define SF_SS RSFT_T(JP_SLSH)
#define AL_X  LALT_T(JP_X)
#define AL_DT RALT_T(JP_DOT)
#define RA_SP LT(RAISE, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung34(
    CT_Q,    JP_W,    JP_E,    JP_R,    JP_T,          JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,
    JP_A,    JP_S,    JP_D,    JP_F,    JP_G,          JP_H,    JP_J,    JP_K,    JP_L,    KC_ENT,
    SF_Z,    AL_X,    JP_C,    JP_V,    JP_B,          JP_N,    JP_M,    CT_CM,   AL_DT,   SF_SS,
                      KC_TAB,  KC_BSPC, LOWER,              RA_SP
  ),

  [_LOWER] = LAYOUT_reviung34(
    JP_EXLM, JP_AT,   JP_HASH, JP_DLR,  JP_PERC,       JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN,
    JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, JP_PIPE,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, JP_SCLN,
    KC_LSFT, KC_ESC,  KC_LGUI, KC_LALT, JP_QUOT,       KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_BSPC,
                      _______, _______, _______,            _______
  ),
  
  [_RAISE] = LAYOUT_reviung34(
    JP_1,    JP_2,    JP_3,    JP_4,    JP_5,          JP_6,    JP_7,    JP_8,    JP_9,    JP_0,
    JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_YEN,        JP_BSLS, XXXXXXX, JP_GRV,  JP_TILD, JP_COLN,
    KC_LSFT, KC_ESC,  KC_RGUI, KC_LALT, JP_DQUO,       KC_TAB,  XXXXXXX, KC_RCTL, KC_RALT, KC_DEL,
                      _______, _______, _______,            _______
  ),
  
  [_ADJUST] = LAYOUT_reviung34(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_F11,  KC_F12,  KC_CAPS, XXXXXXX, XXXXXXX,       QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, _______, _______,            _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
