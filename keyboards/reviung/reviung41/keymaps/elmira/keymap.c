/* Copyright 2020 gtips
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,           KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    LSFT_T(KC_ESC),   KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LCTL,          KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                            KC_LALT,   LT(1,KC_ENT),    KC_SPC,   LT(2,KC_BSPC),    KC_LGUI
  ),
  
  [_LOWER] = LAYOUT(
    KC_TAB,                             KC_1,   KC_2,   KC_3,  KC_4,   KC_5,            KC_LPRN,  KC_RPRN,  KC_LBRC,  KC_RBRC,  KC_GRV,  XXXXXXX,
    LSFT_T(KC_ESC),                     KC_6,   KC_7,   KC_8,  KC_9,   KC_0,            KC_BTN1,  KC_BTN2,  KC_LCBR,    KC_RCBR,  KC_TILD,   XXXXXXX,
    MT(MOD_LCTL | MOD_LSFT, KC_LCTL),   KC_ACL2,   KC_ACL1,  KC_ACL0,  KC_BRID,   KC_BRIU,            KC_MS_L,  KC_MS_D,   KC_MS_U,  KC_MS_R,  KC_WH_U,  KC_WH_D,
                                            KC_LALT,   XXXXXXX,  KC_SPC,   RAISE,  KC_DEL
  ),
  
  [_RAISE] = LAYOUT(
    KC_TAB,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,               KC_HOME,     KC_END,     KC_PGUP,     KC_PGDN,     KC_PSCR,  KC_INS,
    KC_LSFT,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_MINS,   KC_EQL,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,    KC_VOLU,    XXXXXXX,
    KC_LCTL,  XXXXXXX,   XXXXXXX,  XXXXXXX,  KC_UNDS,   KC_PLUS,            KC_SLEP,    KC_MPRV,    KC_MPLY,    KC_MNXT,   KC_VOLD,   KC_MUTE,
                                            KC_LALT,   LOWER,  KC_SPC,  XXXXXXX,  KC_DEL
  ),
  
  [_ADJUST] = LAYOUT(
    KC_F1,     KC_F2,   KC_F3,    KC_F4,    KC_F5,     KC_F6,             KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
    XXXXXXX,   KC_P1,   KC_P2,    KC_P3,    KC_P4,     KC_P5,             KC_P6,    KC_P7,    KC_P8,    KC_P9,    KC_P0,     KC_CAPS,
    QK_BOOT,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_LALT,           KC_RALT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            XXXXXXX,   XXXXXXX,  BL_TOGG,  XXXXXXX,  XXXXXXX
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

