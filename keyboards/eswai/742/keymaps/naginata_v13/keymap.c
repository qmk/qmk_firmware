/* Copyright 2020 eswai
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
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB        ,KC_Y   ,KC_R   ,KC_O    ,KC_U   ,KC_COMM, KC_NO    , KC_NO   ,KC_DOT ,KC_BSPC,KC_L   ,KC_F   ,KC_P    ,KC_QUOT , \
    CTL_T(KC_ESC) ,KC_D   ,KC_S   ,KC_A    ,KC_I   ,KC_G   , KC_NO    , KC_NO   ,KC_J   ,KC_E   ,KC_H   ,KC_T   ,KC_K    ,KC_SCLN , \
    KC_LSFT       ,KC_V   ,KC_Z   ,KC_X    ,KC_M   ,KC_C   , KC_NO    , KC_NO   ,KC_N   ,KC_W   ,KC_B   ,KC_Q   ,KC_SLSH ,KC_UP   , \
    KC_LCTL       ,KC_LWIN,KC_LALT,KC_LCTL,MO(_LOWER),LSFT_T(KC_SPC)  ,LSFT_T(KC_ENT)   ,MO(_RAISE),KC_RSFT,KC_LEFT,KC_DOWN ,KC_RGHT
    ),

  [_LOWER] = LAYOUT(
    _______,XXXXXXX,XXXXXXX,KC_COLN,KC_SCLN,XXXXXXX,XXXXXXX, XXXXXXX, KC_SLSH,KC_7   ,KC_8   ,KC_9   ,KC_MINS,KC_DEL , \
    _______,XXXXXXX,KC_LBRC,KC_LCBR,KC_LPRN,KC_LT  ,XXXXXXX, XXXXXXX, KC_ASTR,KC_4   ,KC_5   ,KC_6   ,KC_PLUS,_______, \
    _______,XXXXXXX,KC_RBRC,KC_RCBR,KC_RPRN,KC_GT  ,XXXXXXX, XXXXXXX, KC_0   ,KC_1   ,KC_2   ,KC_3   ,KC_EQL ,_______, \
    _______,_______,_______,_______,_______, XXXXXXX,        XXXXXXX         ,_______,_______,_______,_______,_______
  ),

  [_RAISE] = LAYOUT(
    _______   ,KC_TILD   ,KC_AT     ,KC_HASH   ,KC_DLR    ,KC_PERC,XXXXXXX, XXXXXXX ,XXXXXXX   ,KC_HOME   ,KC_UP     ,KC_END    ,XXXXXXX   ,KC_DEL    , \
    _______   ,KC_CIRC   ,KC_AMPR   ,KC_EXLM   ,KC_QUES   ,KC_JYEN,XXXXXXX, XXXXXXX ,XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,_______   , \
    _______   ,KC_PIPE   ,KC_GRV    ,KC_QUOT   ,KC_DQT    ,KC_UNDS,XXXXXXX, XXXXXXX ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,XXXXXXX, XXXXXXX    ,_______   ,_______   ,_______   ,_______   ,_______
  ),

  [_ADJUST] = LAYOUT(
    _______,XXXXXXX,RESET,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,RESET  ,KC_PWR  ,_______, \
    _______,XXXXXXX,KC_SLEP,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX ,_______, \
    _______,XXXXXXX,XXXXXXX,XXXXXXX,KC_MYCM,KC_CALC,XXXXXXX, XXXXXXX,XXXXXXX,KC_WAKE,XXXXXXX,XXXXXXX,XXXXXXX,_______, \
    _______,_______,_______,_______,_______,     XXXXXXX,     XXXXXXX,_______,_______,_______,_______,_______
  ),

  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,XXXXXXX, XXXXXXX,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,XXXXXXX, XXXXXXX,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,XXXXXXX, XXXXXXX,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
    _______,_______,_______,_______,_______,   NG_SHFT,         NG_SHFT2,_______,_______,_______,_______,_______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_J, KC_E};
  uint16_t ngoffkeys[] = {KC_I, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // set_naginata(_NAGINATA);
  // set_unicode_input_mode(UC_WINC);
  set_unicode_input_mode(UC_LNX);
  // 薙刀式
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void naginata_logo(void) {
    static const char PROGMEM ng_logo[] = {
      0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6
    };
    oled_write_P(ng_logo, false);
}

// static void colevrak_logo(void) {
//     static const char PROGMEM cv_logo[] = {
//       0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc
//     };
//     oled_write_P(cv_logo, false);
// }

#define FRAME_TIMEOUT (1000/30)
static uint16_t anim_timer = 0;

void oled_task_user(void) {
  if (timer_elapsed(anim_timer) > FRAME_TIMEOUT) {
    anim_timer = timer_read();
    oled_clear();
    if (is_keyboard_master()) {
      if (naginata_state()) {
        oled_write_ln_P(PSTR("   "), false);
        oled_write_ln_P(PSTR("     NAGINATA V13"), false);
        oled_write_ln_P(PSTR("   "), false);
        oled_write_ln_P(PSTR("   "), false);
      } else {
        oled_write_ln_P(PSTR("   "), false);
        oled_write_ln_P(PSTR("      COLEVRAK"), false);
        oled_write_ln_P(PSTR("   "), false);
        oled_write_ln_P(PSTR("   "), false);
      }
    } else {
      naginata_logo();
    }
  }
}
#endif