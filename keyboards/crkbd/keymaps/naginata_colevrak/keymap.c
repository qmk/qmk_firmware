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
#include "twpair_on_jis.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

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
  _ADJUST,
};

enum custom_keycodes {
  EISU = NG_SAFE_RANGE,
  KANA2,
  LCTOGL, // Macのライブ変換対応オンオフ
  RGBRST,
};

#define CTLSPC  CTL_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      KC_TAB ,KC_Y   ,KC_R   ,KC_O   ,KC_U   ,KC_COMM,                KC_DOT ,KC_BSPC,KC_L   ,KC_F   ,KC_P   ,KC_QUOT, \
CTL_T(KC_ESC),KC_D   ,KC_S   ,KC_A   ,KC_I   ,KC_G   ,                KC_J   ,KC_E   ,KC_H   ,KC_T   ,KC_K   ,KC_SCLN, \
      KC_LSFT,KC_V   ,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,                KC_N   ,KC_W   ,KC_B   ,KC_Q   ,KC_SLSH,KC_RALT, \
                             KC_LWIN,MO(_LOWER),SFT_T(KC_SPC),SFT_T(KC_ENT),MO(_RAISE),KC_APP
  ),

  [_LOWER] = LAYOUT(
    RGB_TOG   ,LCTOGL    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,           JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,KC_BSPC, \
    RGB_MOD   ,XXXXXXX   ,JP_LBRC   ,JP_LCBR   ,JP_LPRN   ,KC_LT     ,           JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,JP_DOT , \
    RGBRST   ,XXXXXXX   ,JP_RBRC   ,JP_RCBR   ,JP_RPRN   ,KC_GT     ,           KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,JP_COMM, \
                                    _______,_______,_______,KANA2  ,_______,_______
  ),

  [_RAISE] = LAYOUT(
    _______,JP_TILD,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,                           XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,KC_PGUP   ,XXXXXXX   , \
    _______,JP_CIRC,JP_AMPR,JP_EXLM,JP_QUES,JP_BSLS,                           KC_HOME   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,KC_PGDN   ,XXXXXXX   , \
    _______,JP_PIPE,JP_GRV ,JP_QUOT,JP_DQUO ,JP_UNDS,                           KC_END    ,S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),XXXXXXX   ,XXXXXXX   , \
                                                _______   ,_______,EISU         ,_______   ,_______   ,_______
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______   ,_______,_______         ,_______   ,_______   ,_______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
                                    _______,_______,NG_SHFT,NG_SHFT2,_______,_______
  ),
// 薙刀式

};

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_J, KC_E};
  uint16_t ngoffkeys[] = {KC_I, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);

  #ifdef NAGINATA_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  #ifdef NAGINATA_EDIT_WIN
  set_unicode_input_mode(UC_WINC);
  #endif
  // 薙刀式
}


int RGB_current_mode;

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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    }

  // 薙刀式
    if (!process_naginata(keycode, record))
      return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}
