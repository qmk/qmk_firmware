/* Copyright 2022 kkokdae <kkokdae@me.com>
 *
 *  This program is free software: you can redistribute it and/or modify
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

enum my_layers {
  _COLEMAK,
  _QWERTY,
  _FUNC,
  _NUMPAD,
  _SYMBOL
};

enum my_tds {
  TdH,
  TdL
};

#define FUNC LT(_FUNC, KC_SPC)
#define NUMPAD  LT(_NUMPAD, KC_BSPC)
#define DNUMPAD LT(_NUMPAD, KC_DEL)
#define SYMBOL OSL(_SYMBOL)

#define OSMCMD OSM(MOD_LGUI)
#define OSMOPT OSM(MOD_LALT)
#define OSMCTL OSM(MOD_LCTL)
#define OSMSFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
      KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
      KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
      KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    _______, _______, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_ENT,
			OSMCMD,  OSMOPT,  OSMCTL,  OSMSFT,  FUNC,    KC_TAB,  KC_ESC,  NUMPAD,  SYMBOL,  OSMCTL,  OSMOPT,  OSMCMD
      ),

  [_QWERTY] = LAYOUT(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENT,
			OSMCMD,  OSMOPT,  OSMCTL,  OSMSFT,  FUNC,    KC_TAB,  KC_ESC,  NUMPAD,  SYMBOL,  OSMCTL,  OSMOPT,  OSMCMD
      ),

  [_FUNC] = LAYOUT(
      KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD, KC_MPLY,                   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_CAPS,
      KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_BRIU,                   KC_F12,  KC_F4,   KC_F5,   KC_F6,   TD(TdL),
      KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_BRID, _______, _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,
      _______, _______, _______, KC_ASTG, _______, _______, _______, DNUMPAD, _______, _______, _______, _______
      ),

  [_NUMPAD] = LAYOUT(
      _______, _______, _______, _______, _______,                   S(KC_E), KC_7,    KC_8,    KC_9,    S(KC_F),
      TD(TdL), KC_EQL,  KC_ASTR, KC_PLUS, _______,                   S(KC_C), KC_4,    KC_5,    KC_6,    S(KC_D),
      TD(TdH), KC_DOT,  KC_SLSH, KC_MINS, _______, _______, _______, S(KC_A), KC_1,    KC_2,    KC_3,    S(KC_B),
      _______, _______, _______, KC_ASTG, _______, _______, _______, _______, KC_0,    _______, _______, _______
      ),

  [_SYMBOL] = LAYOUT(
      KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_CIRC,                   KC_DLR,  KC_BSLS, KC_PERC, KC_AT,   KC_DQUO,
      KC_QUES, KC_EXLM, KC_HASH, KC_ASTR, KC_AMPR,                   KC_PIPE, KC_MINS, KC_PLUS, KC_UNDS, KC_EQL,
      KC_LT,   KC_LPRN, KC_RPRN, KC_GT,   KC_GRV,  _______, _______, KC_TILD, KC_SLSH, C(KC_B), KC_COLN, KC_SCLN,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      ),
};

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case KC_MINS:
		case KC_UNDS:
		case KC_BSPC:
			return false;
	}

	switch(keycode & 0xFF) {
		case KC_1 ... KC_UP:
			autoshift_disable();
		default:
			return false;
	}
}

void dance_hex(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
			SEND_STRING("0x");
      break;
    case 2:
			SEND_STRING("\\x");
      break;
  }
}

void dance_lang(qk_tap_dance_state_t *state, void *user_data) {
  uint32_t default_layer;
  switch(state->count) {
    case 1:
			SEND_STRING(SS_LCTL(" ") SS_DELAY(200) SS_TAP(X_ENT));
    case 2:
      default_layer = get_highest_layer(default_layer_state);
      if (default_layer == _COLEMAK) {
        set_single_persistent_default_layer(_QWERTY);
      }
      else if (default_layer == _QWERTY) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      break;
  }
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [TdH] = ACTION_TAP_DANCE_FN(dance_hex),
  [TdL] = ACTION_TAP_DANCE_FN(dance_lang)
};
