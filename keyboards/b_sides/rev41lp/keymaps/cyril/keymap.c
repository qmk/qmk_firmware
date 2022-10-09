/*
Copyright 2021 @cyril279

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NAVIG,
    _FUNCTION
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define SPC_NAV LT(_NAVIG,KC_SPC)
#define FUNCT  MO(_FUNCTION)
#define NAVIG  MO(_NAVIG)

#define LGUI_A LGUI_T(KC_A)
#define LALT_S LALT_T(KC_S)
#define LSFT_D LSFT_T(KC_D)
#define LCTL_F LCTL_T(KC_F)
#define RCTL_J RCTL_T(KC_J)
#define RSFT_K RSFT_T(KC_K)
#define RALT_L LALT_T(KC_L)
#define RGUI_SCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_rev41lp(
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_ESC,     KC_A,  LALT_S,  LSFT_D,  LCTL_F,    KC_G,             KC_H,  RCTL_J,  RSFT_K,  RALT_L, KC_SCLN, KC_QUOT,
    KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                        KC_LGUI,   LOWER, SPC_NAV,   RAISE,   FUNCT
  ),

  [_LOWER] = LAYOUT_rev41lp(
    KC_GRV,  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
    _______, _______, _______, _______, _______, _______,          KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, KC_LGUI, KC_LALT, KC_CAPS, _______,          KC_PSCR, _______, _______, _______, _______, _______,
                                        _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_rev41lp(
    KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,       KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
    _______, _______, _______, _______, _______, _______,          KC_GRV,  KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, KC_LGUI, KC_LALT, KC_CAPS, _______,          KC_PSCR, _______, _______, _______, _______, _______,
                                        _______, _______, _______, _______, _______
  ),

  [_NAVIG] = LAYOUT_rev41lp(
    KC_DEL,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_DEL,
    _______, _______, _______, _______, _______, _______,          _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,
    _______, _______, KC_LGUI, KC_LALT, KC_CAPS, _______,          _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,
                                        _______, _______, _______, _______, _______
  ),

  [_FUNCTION] = LAYOUT_rev41lp(
    KC_DEL,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_DEL,
    _______, _______, _______, _______, _______, _______,            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    _______, _______, KC_LGUI, KC_LALT, KC_CAPS, _______,            KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
                                        _______, _______, _______, _______, _______
  ),

    [_ADJUST] = LAYOUT_rev41lp(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  BL_DEC, BL_TOGG,          BL_BRTG,  BL_INC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_A:
        case RGUI_SCLN:
        case LALT_S:
        case RALT_L:
        case LCTL_F:
        case RCTL_J:
        case SPC_NAV:
            return 225;
        default:
            return TAPPING_TERM;
    }
}
