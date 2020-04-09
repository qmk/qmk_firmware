/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _NAGINATA 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
};

const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
};

// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
      }
      break;
  }
}
// 薙刀式

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | Ctrl | LOWER|  Sp  |           |  Sp  | RAISE| Shift|
 *               `--------------------'           `--------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                   KC_LCTL,  LOWER,   KC_SPC,       KC_SPC,  RAISE,   KC_LSFT \
),

/* Raise テンキーと記号
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  `   |  &   |  *   |  (   |  )   |           |  =+  |  7&  |  8*  |  9(  |  0)  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |  $   |  %   |  ^   |      |           |  '"  |  4$  |  5%  |  6^  |  \|  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  (   |  !   |  @   |  #   |  )   |           |  [{  |  1!  |  2@  |  3#  |  ]}  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | Ctrl |      | Shift|           |  0)  |@@@@@@| Win  |
 *               `--------------------'           `--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  S(KC_7), S(KC_8), S(KC_9), S(KC_0),      KC_EQL,  KC_7, KC_8,  KC_9, KC_0,  \
  _______, S(KC_4), S(KC_5), S(KC_6), _______,      KC_QUOT, KC_4, KC_5,  KC_6, KC_BSLS, \
  KC_LPRN, S(KC_1), S(KC_2), S(KC_3), KC_RPRN,      KC_LBRC, KC_1, KC_2,  KC_3, KC_RBRC, \
                    KC_LCTL, _______, KC_LSFT,      KC_0,    _______, KC_LGUI  \
),

/* Lower 制御系と左手テンキー
 *
 * ,----------------------------------.           ,----------------------------------.
 * | Esc  |  7&  |  8*  |  9(  |  0)  |           | Home | BkSp |  -_  |  Del | Esc  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Tab  |  4$  |  5%  |  6^  |      |           | Left | Up   | Right|      | Ent  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  (   |  1!  |  2@  |  3#  |   )  |           | End  | Down | Tab  |      |      |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |  0)  |@@@@@@|      |           | Shift|      | Win  |
 *               `--------------------'           `--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_ESC,  KC_7, KC_8, KC_9, KC_0,           KC_HOME, KC_BSPC, KC_MINS, KC_DEL,  KC_ESC,  \
  KC_TAB,  KC_4, KC_5, KC_6, _______,        KC_LEFT, KC_UP,   KC_RGHT, _______, KC_ENT,  \
  S(KC_9), KC_1, KC_2, KC_3, S(KC_0),        KC_END,  KC_DOWN, KC_TAB,  _______, _______, \
                 KC_0, _______, _______,     KC_LSFT, _______, KC_LGUI \
),


/* Adjust (Lower + Raise) Fキーと特殊
 *
 * ,----------------------------------.           ,----------------------------------.
 * | Reset|      |      |      |      |           |      |  F7  |  F8  |  F9  | Reset|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      | Vol- | Mute | Vol+ |           |      |  F4  |  F5  |  F6  |  F11 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      | Prev | Play | Next |           |      |  F1  |  F2  |  F3  |  F12 |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      |      |      |           |  F10 |      |      |
 *               `--------------------'           `--------------------'
 */
[_ADJUST] =  LAYOUT( \
  RESET,   _______, _______, _______, _______,      _______, KC_F7,   KC_F8,   KC_F9,   RESET,   \
  _______, _______, KC_VOLD, KC_MUTE, KC_VOLU,      _______, KC_F4,   KC_F5,   KC_F6,   KC_F11, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,      _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  \
                    _______, _______, _______,      KC_F10,  _______, _______  \
),

[_NAGINATA] = LAYOUT(
  NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,NG_Y   ,NG_U   ,NG_I   ,NG_O,NG_P, \
  NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,NG_H   ,NG_J   ,NG_K   ,NG_L,NG_SCLN, \
  NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,NG_N   ,NG_M   ,NG_COMM,NG_DOT,NG_SLSH, \
                  _______,_______,NG_SHFT,NG_SHFT,_______,_______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }

  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  return true;
}

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
  #ifdef NAGINATA_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  #ifdef NAGINATA_EDIT_WIN
  set_unicode_input_mode(UC_WINC);
  #endif
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
