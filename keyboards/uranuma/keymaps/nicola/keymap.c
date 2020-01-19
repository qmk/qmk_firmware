/* Copyright 2019 yohei
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

// Defines the keycodes used by our macros in process_record_user

enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  // NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  KANJI,
  LOWER,
  RAISE,
};


// NICOLA親指シフト
#include "nicola.h"
NGKEYS nicola_keys;
// NICOLA親指シフト


// Layer Mode aliases
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADUJST ADJUST
#define KC_DLBS BASE //DF(_BASE)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KANJI
#define KC_RST   RESET
#define KC_SUSFT SUSFT
#define KC_ZSFT  LSFT_T(KC_Z)
#define KC_MNSF  LSFT_T(KC_MINS)
#define KC_ESCT  LCTL_T(KC_ESC)
#define KC_TBAL  LALT_T(KC_TAB)
#define KC_ALAL  LALT_T(KC_A)
#define KC_11SF  LSFT_T(KC_F11)
#define KC_ALAP  LALT_T(KC_APP)
#define KC_JEQL  LSFT(KC_MINS)
#define KC_WLCK  LALT(KC_L)
#define KC_SFEQ  LSFT(KC_MINS)
#define KC_SFPL  LSFT(KC_SCLN)
#define KC_SFAS  LSFT(KC_QUOT)




  // NICOLA親指シフト
  bool a = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
    update_led();
  }
  if (a == false) return false;
  // NICOLA親指シフト




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //|----------------------------------.                ,----------------------------------.
      KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                    KC_Y, KC_U, KC_I, KC_O, KC_P, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      KC_A,  KC_S, KC_D,  KC_F, KC_G,                KC_H,  KC_J,  KC_K, KC_L,  KC_BSLS, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      KC_ZSFT, KC_X, KC_C, KC_V, KC_B,               KC_N, KC_M, KC_COMM, KC_DOT, KC_MNSF, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      KC_ESCT,KC_TBAL, KC_PSCR, LT(_LOWER, KC_SPC), KC_SPC, KC_SPC, LT(_RAISE, KC_SPC), KC_SLSH, KC_BSLS, KC_RBRC, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      MO(_LOWER), KC_LGUI,               KC_BSPC, KC_ENT,         LALT(KC_GRV), MO(_RAISE) \
  //|------+------+------+------+------|                |------+------+------+------+------|
  ),
// NICOLA親指シフト
  // デフォルトレイヤーに関係なくQWERTYで
  [_NICOLA] = LAYOUT(
  //,----------------------------------.                ,-----------------------------------.
     NG_Q,  NG_W,  NG_E,  NG_R,  NG_T,                   NG_Y,  NG_U,  NG_I,  NG_O,  NG_P, \
  //|------+------+------+------+------|                |------+------+------+------+------|
     NG_A,  NG_S,  NG_D,  NG_F,  NG_G,                   NG_H,  NG_J,  NG_K,  NG_L,NG_SCLN,\
  //|------+------+------+------+------|                |------+------+------+------+------|
     NG_Z,  NG_X,  NG_C,  NG_V,  NG_B,                   NG_N,  NG_M,NG_COMM,NG_DOT,NG_SLSH,\
  //|------+------+------+------+------|                |------+------+------+------+------|
      KC_ESCT,KC_TBAL, KC_PSCR, LT(_LOWER, KC_SPC), KC_SPC, KC_SPC, LT(_RAISE, KC_SPC), KC_SLSH, KC_BSLS, KC_RBRC, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      MO(_LOWER), KC_LGUI,              ,NG_SHFTL,NG_SHFTR,        LALT(KC_GRV), MO(_RAISE)  \
                              //`--------------------'  `--------------------'
  ),
// NICOLA親指シフト

  [_LOWER] = LAYOUT(
  //|---------------------------------------------------------------------------------------------------.
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F11,  KC_F12, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_SCLN, KC_UP,    KC_EQL, \
  //|---------+---------+---------+---------+---------+--------+---------+---------+---------+---------'
      KC_ESCT,KC_TBAL,KC_LGUI, KC_ENT, KC_BSPC, KC_SPC, MO(RAISE), KC_LEFT, KC_DOWN, KC_RGHT, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      MO(_LOWER), KC_LGUI,                 KC_SPC, KC_ENT,                KC_KANJI, MO(_RAISE) \
  //|------+------+------+------+------|                |------+------+------+------+------|
  ),

  [_RAISE] = LAYOUT(
  //|---------------------------------------------------------------------------------------------------.
        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F11,  KC_F12, XXXXXXX,  KANJI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UP,    KC_RO, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
      KC_ESCT,KC_TBAL,KC_LGUI, MO(_LOWER),KC_BSPC, KC_SPC, MO(_RAISE), KC_LEFT, KC_DOWN, KC_RGHT, \
  //|------+------+------+------+------|                |------+------+------+------+------|
      MO(_LOWER), KC_TBAL,                 KC_SPC, KC_ENT,                KC_KANJI, MO(_RAISE) \
  //|------+------+------+------+------|                |------+------+------+------+------|
  ),

};

void matrix_init_user(void) {
  // NICOLA親指シフト
  set_nicola(_NICOLA);
  // NICOLA親指シフト

}


  switch (keycode) {
    case KC_QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;

    case KC_EISU:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_off();
        // NICOLA親指シフト
        update_led();
      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_on();
        // NICOLA親指シフト
        update_led();
      }
      return false;
      break;
  }


void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
