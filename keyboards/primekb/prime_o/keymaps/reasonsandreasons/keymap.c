/* Copyright 2018 Jumail Mundekkat
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

#define L1BS LT(2, KC_BSPC)
#define LSUP LSFT_T(KC_UP)
#define CTLL LCTL_T(KC_LEFT)
#define ECTL LCTL_T(KC_ESC)
#define ALLM ALL_T(KC_MINS)
#define SCLS LT(3, KC_SCLN)

// Establishes tap dance keys
enum {
  TD_SPC_ENT = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)

};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,---------------------------------------------------------------------------------------------------------------,
 * |  `   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | Del  | NMLK |  /   |  *   |  -   |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |  \   |  7   |  8   |  9   |  +   |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   |  4   |  5   |  6   |  =   |
 * | Ctrl |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |  Up  |  1   |  2   |  3   |      |
 * | Shift|      |      |      |      |      |      |      |      |      |      | Shift|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+ Enter|
 * |  -   |      |      |      |  Backspace  |    Space    |      |      | Left | Down | Right|  0   |  .   |      |
 * | ALL  | Ctrl | Alt  | GUI  |     Fn1     |             | GUI  | Alt  | Ctrl |      |      |      |      |      |
 * `---------------------------------------------------------------------------------------------------------------'
 */

  [0] = LAYOUT(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,  KC_5,  KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_DEL,   KC_NLCK,   KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,  KC_T,  KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,  KC_7,      KC_8,     KC_9,     KC_PPLS,
    ECTL,     KC_A,     KC_S,     KC_D,     KC_F,  KC_G,  KC_H,    KC_J,    KC_K,     KC_L,     SCLS,     KC_QUOT,  KC_4,      KC_5,     KC_6,     KC_PEQL,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,  KC_B,  KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  LSUP,     KC_1,      KC_2,     KC_3,     KC_ENT,
    ALLM,     KC_LCTL,  KC_LALT,  KC_LGUI,  L1BS,  L1BS,  KC_SPC,  KC_SPC,  KC_RGUI,  KC_RALT,  CTLL,     KC_DOWN,  KC_RIGHT,  KC_0,     KC_PDOT,  KC_ENT
  ),

/* GAME
 * ,---------------------------------------------------------------------------------------------------------------,
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | Del  | NMLK |  /   |  *   |  -   |
 * |  `   |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | '    |  7   |  8   |  9   |  +   |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   | Rtrn |  4   |  5   |  6   |  =   |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |  Up  |  1   |  2   |  3   |      |
 * | Shift|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+ Enter|
 * |      |      |      |      |    Space    |  Backspace  |      |      | Left | Down | Right|  0   |  .   |      |
 * | Fn1  | Ctrl | Alt  | Alt  |             |             | GUI  | DF(0)|      |      |      |      |      |      |
 * `---------------------------------------------------------------------------------------------------------------'
 */

  [1] = LAYOUT(
    KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,    KC_5,    KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     KC_DEL,   KC_NLCK,   KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,    KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,     KC_QUOT,  KC_7,      KC_8,     KC_9,     KC_PPLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,    KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_ENT,   KC_4,      KC_5,     KC_6,     KC_PEQL,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,    KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_UP,    KC_1,      KC_2,     KC_3,     KC_ENT,
    MO(2),    KC_LCTL,  KC_LALT,  KC_LALT,  KC_SPC,  KC_SPC,  KC_BSPC,  KC_BSPC,  KC_RGUI,  DF(0),   KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_0,     KC_PDOT,  KC_ENT
  ),

/* SYMBOL
 * ,---------------------------------------------------------------------------------------------------------------,
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+-------------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  #   |  [   |  <   |  >   |  ]   |  _   |  |   |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  ~   |  (   |  {   |  }   |  )   |  @   |  -   |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+      |
 * |      |      |      |      |             |    Enter    |      |      |      |      |      |      |      |      |
 * |      |      |      |      |             |             |      |      |      |      |      |      |      |      |
 * `---------------------------------------------------------------------------------------------------------------'
 */

	[2] = LAYOUT(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_HASH,  KC_LBRC,  KC_LT,    KC_GT,    KC_RBRC,  KC_UNDS,  KC_PIPE,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_TILD,  KC_LPRN,  KC_LCBR,  KC_RCBR,  KC_RPRN,  KC_AT,    KC_MINS,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_ENT,   KC_ENT,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

/* SYSTEM
 * ,---------------------------------------------------------------------------------------------------------------,
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+-------------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | PgUp | Home |  Up  | End  |      |      | Vol- | Vol+ | Mute |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | PgDn | Left | Down |Right |      |      | Play | Prev | Next |      |      |      |      |      | QK_BOOT|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------|------+------+------+------+------+------+------+------+------+------+------+------+------+  BL  |
 * |      |      |      |      |             |             |      |      |      |      |      |      |  BL  | TGGL |
 * | GAME |      |      |      |             |             |      |      |      |      |      |      | STEP |      |
 * `---------------------------------------------------------------------------------------------------------------'
 */

	[3] = LAYOUT(
    _______,  _______,  _______,  _______,  _______, _______,  _______,  _______,      _______,    _______,   _______,  _______,  _______,  _______,  _______,   _______,
    _______,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,  _______,  _______,  KC__VOLDOWN,  KC__VOLUP,  KC__MUTE,  _______,  _______,  _______,  _______,  _______,   _______,
    _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  KC_MPLY,     KC_MRWD,    KC_MFFD,   _______,  _______,  _______,  _______,  _______,   QK_BOOT,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,    _______,   _______,  _______,  _______,  _______,  _______,   BL_TOGG,
    DF(1),    _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,    _______,   _______,  _______,  _______,  _______,  BL_STEP,  BL_TOGG
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
