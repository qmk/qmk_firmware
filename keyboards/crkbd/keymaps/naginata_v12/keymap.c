/* Copyright 2018-2019 eswai <@eswai>
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#include "keymap_jp.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

enum keymap_layers {
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
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

enum custom_keycodes {
  EISU = NG_SAFE_RANGE,
  KANA2,
  LCTOGL, // Macのライブ変換対応オンオフ
};

#define CTLSPC  CTL_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                KC_H   ,KC_J   ,KC_K   ,KC_L   ,JP_SCLN,KC_LALT, \
    KC_LCTL,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                KC_N   ,KC_M   ,JP_COMM,JP_DOT ,JP_SLSH,KC_RSFT, \
                                 MO(_LOWER),KC_LSFT,CTLSPC ,CTLENT ,KC_RSFT,MO(_RAISE)
  ),

  [_LOWER] = LAYOUT(
    _______,JP_TILD,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,                JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,KC_BSPC, \
    _______,JP_CIRC,JP_AMPR,JP_EXLM,JP_QUES,JP_BSLS,                JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,JP_DOT , \
    _______,JP_PIPE,JP_GRV ,JP_QUOT,JP_DQT ,JP_UNDS,                KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,JP_COMM, \
                                    _______,_______,_______,_______,KANA2  ,_______
  ),

  [_RAISE] = LAYOUT(
    _______   ,LCTOGL    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,                      XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,KC_PGUP   ,XXXXXXX   , \
    _______   ,XXXXXXX   ,JP_LBRC   ,JP_LCBR   ,JP_LPRN   ,JP_LT     ,                      KC_HOME   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,KC_PGDN   ,XXXXXXX   , \
    _______   ,XXXXXXX   ,JP_RBRC   ,JP_RCBR   ,JP_RPRN   ,JP_GT     ,                      KC_END    ,S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),XXXXXXX   ,XXXXXXX   , \
                                                _______   ,EISU      ,_______   ,_______   ,_______   ,_______
  ),

  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
                                    _______,NG_SHFT,_______,_______,NG_SHFT,_______
  ),
// 薙刀式

};

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
  #ifdef NAGINATA_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  #ifdef NAGINATA_EDIT_WIN
  set_unicode_input_mode(UC_WINC);
  #endif
  // 薙刀式
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
      }
      return false;
      break;
    case LCTOGL:
      if (record->event.pressed) {
        mac_live_conversion_toggle();
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
