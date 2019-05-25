/* Copyright 2019 Kyle Terry
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

#define LOWER       MO(_LOWER)
#define RAISE       MO(_RAISE)
#define NUM         MO(_NUM)
#define CTL_ESC     CTL_T(KC_ESC)
#define OS_LGUI     OSM (MOD_LGUI)
#define SGAME       TO(_GAMING)
#define SQWER       TO(_QWERTY)

enum layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM
};

enum {
  /* tap dance for raise and lower layer switching */
  TD_RL = 0,
  /* tap dance for common cording */
  TD_C  = 1,
  /* tap dance for media keys */
  TD_MD = 2,
};

/*  layer template:
 *  [_LAYER] = LAYOUT(
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
 *  ),
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_LCTL,    TD(TD_C),KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_LALT,    KC_ENT,  KC_H,    KC_J,   KC_K,    KC_L,     KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   NUM,        OS_LGUI, KC_N,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,
        KC_LCTL,                        OS_LGUI, KC_SPC, LOWER,      RAISE,   KC_SPC,  OS_LGUI,                        KC_RALT
  ),

  [_GAMING] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_LCTL,    TD(TD_C),KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_ESC,     KC_ENT,  KC_H,    KC_J,   KC_K,    KC_L,     KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   NUM,        OS_LGUI, KC_N,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,
        KC_LALT,                        KC_V,    KC_SPC, LOWER,      RAISE,   KC_SPC,  OS_LGUI,                        KC_RALT
  ),

  [_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LPRN,   KC_RPRN, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_LBRC,   KC_RBRC, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, KC_LCBR,   KC_RCBR, _______, _______, _______, _______, TD(TD_MD), KC_MNXT,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  ),

  [_RAISE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,   _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, KC_PGUP, _______, _______, _______, SQWER,     _______, _______, _______, KC_INS,  _______, KC_PSCR, _______,
    _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, SGAME,     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  ),

  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_ASTR,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_MINS,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_PLUS,
        _______,                        _______, _______, _______,   _______, _______, _______,                        KC_0
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void td_common(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      /* this case handles ctrl+o which is my tmux prefix
       */
      tap_code16(C(KC_O));
      reset_tap_dance(state);
      break;
    case 2:
      /* this case handles shift+insert which is a common way
       * for me to paste text in linux
       */
      tap_code16(S(KC_INS));
      reset_tap_dance(state);
      break;
  }
}

void td_media(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_MPLY);
      reset_tap_dance(state);
      break;
    case 2:
      tap_code16(KC_MUTE);
      reset_tap_dance(state);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_C]  = ACTION_TAP_DANCE_FN(td_common),
  [TD_MD] = ACTION_TAP_DANCE_FN(td_media),
};
