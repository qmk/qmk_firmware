/* Copyright 2021 Brandon Lewis
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
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _MEDIA,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  MEDIA,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TAB,    KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,            KC_Y,           KC_U,   KC_I,  KC_O,      KC_P,    KC_BSPC, \
        KC_ESC,    KC_A,    KC_S,    KC_D,     KC_F,   KC_G,            KC_H,           KC_J,   KC_K,  KC_L,      KC_SCLN, KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,            KC_ENT,         KC_N,   KC_M,  KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI, _______, KC_LALT,  LOWER,  KC_SPC, KC_MUTE, LCTL(KC_BSPC),  RAISE,  MEDIA, _______,   KC_LEAD, KC_END
    ),
    [_COLEMAK] = LAYOUT(
        KC_TAB,    KC_Q,    KC_W,    KC_F,     KC_P,   KC_G,            KC_J,           KC_L,   KC_U,  KC_Y,      KC_SCLN, KC_BSPC, \
        KC_ESC,    KC_A,    KC_R,    KC_S,     KC_T,   KC_D,            KC_H,           KC_N,   KC_E,  KC_I,      KC_O,    KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,            KC_ENT,         KC_K,   KC_M,  KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI, _______, KC_LALT,  LOWER,  KC_SPC, KC_MUTE, LCTL(KC_BSPC),  RAISE,  MEDIA, _______,   KC_LEAD, KC_END
    ),
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,             KC_CIRC, KC_AMPR,  KC_ASTR,      KC_LPRN,  KC_RPRN,  KC_DEL,  \
        KC_GRV,  KC_1,    KC_2,     KC_3,     KC_4,      KC_5,                KC_6,    KC_7,     KC_8,         KC_9,     KC_0,     KC_BSLS, \
        _______, KC_LCBR, KC_RCBR,  KC_LBRC,  KC_RBRC,   SGUI(KC_S),          _______, _______,  KC_MINS,      KC_UNDS,  KC_EQL,   KC_PLUS, \
        KC_RCTL, _______, _______,  _______,  _______,   _______,    _______, _______, RAISE,    LCTL(KC_DEL), _______,  _______,  KC_HOME
    ),
    [_RAISE] = LAYOUT(
        _______,   KC_F1,    KC_F2,    KC_F3,     KC_F4,     _______,           KC_PGUP,   _______,    KC_UP,     _______,   _______,   _______, \
		KC_CAPS,   KC_F5,    KC_F6,    KC_F7,     KC_F8,     _______,           KC_PGDN,   KC_LEFT,    KC_DOWN,   KC_RIGHT,  _______,   KC_PIPE, \
		_______,   KC_F9,    KC_F10,   KC_F11,    KC_F12,    _______,           _______,   _______,    _______,   _______,   _______,   _______, \
		_______,   _______,  _______,  _______,   LOWER,     _______, _______,  _______,   _______,    _______,   _______,   _______,   _______
    ),
    [_MEDIA] = LAYOUT(
        DM_RSTP,  DM_REC1,   DM_REC2,   _______,   _______,    _______,          _______,   KC_MPLY,  KC_VOLU, KC_MUTE, _______,   KC_MSEL, \
		_______,  DM_PLY1,   DM_PLY2,   _______,   _______,    _______,          _______,   KC_MPRV,  KC_VOLD, KC_MNXT, _______,   _______, \
		_______,  _______,   _______,   _______,   _______,    _______,          _______,   _______,  _______, _______, _______,   _______, \
		_______,  _______,   _______,   _______,   _______,    _______,	_______, _______,   _______,  _______, _______, _______,   _______
    ),
    [_ADJUST] = LAYOUT(
        _______,   _______,   _______,   _______,   _______,    _______,          _______,   _______,    _______,   _______,   _______,   RESET,   \
		_______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_SAI,    RGB_VAI,          _______,   QWERTY,     COLEMAK,   _______,   _______,   _______, \
		_______,   _______,   _______,   _______,   _______,    _______,          _______,   OUT_AUTO,   OUT_USB,   OUT_BT,    _______,   _______, \
		_______,   _______,   _______,   _______,   _______,    _______, _______, _______,   _______,    _______,   _______,   _______,   _______
    ),
};

// OLED and Encoder function is located in the ristretto.c File

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
		case MEDIA:
            if (record->event.pressed) {
                layer_on(_MEDIA);
            } else {
                layer_off(_MEDIA);
            }
            return false;
            break;
        }
    return true;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY(){
		leading = false;
		leader_end();

        SEQ_ONE_KEY(KC_BSPC){
            SEND_STRING(SS_LCTRL("`"));
        }
        SEQ_ONE_KEY(KC_QUOT){
            SEND_STRING(SS_LCTRL(SS_LSFT("p")));
        }
	}
};
