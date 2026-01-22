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
#include "os_detection.h"
// #include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式
#define NAGINATA_TIMEOUT 30000

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _WIN,
  _MAC,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KANAON = NG_SAFE_RANGE,
    EISUON,
};

static deferred_token my_token;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WIN] = LAYOUT(
//            ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	  	KC_GRV  ,KC_1     ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,KC_EQL  ,KC_HOME ,KC_END  , \
		  KC_TAB  ,KC_K     ,KC_D    ,KC_N    ,KC_F    ,KC_Q    ,KC_J    ,KC_BSPC ,KC_R    ,KC_U    ,KC_P    ,KC_QUOT ,KC_DEL  , \
CTL_T(KC_ESC) ,KC_W     ,KC_I    ,KC_S    ,KC_A    ,KC_G    ,KC_Y    ,KC_E    ,KC_T    ,KC_H    ,KC_B    ,KC_SCLN ,KC_ENT  , \
		  KC_LSFT ,KC_Z     ,KC_X    ,KC_V    ,KC_C    ,KC_L    ,KC_M    ,KC_O    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_LBRC ,KC_UP   ,KC_RBRC, \
		  KC_LCTL ,KC_LWIN  ,MO(_LOWER)       ,LSFT_T(KC_SPC)   ,LSFT_T(KC_ENT)   ,MO(_RAISE)       ,KC_LALT ,KC_LEFT ,KC_DOWN ,KC_RGHT
  ),

  [_MAC] = LAYOUT(
//            ,         ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	  	KC_GRV  ,KC_1     ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,KC_EQL  ,KC_HOME ,KC_END  , \
		  KC_TAB  ,KC_K     ,KC_D    ,KC_N    ,KC_F    ,KC_Q    ,KC_J    ,KC_BSPC ,KC_R    ,KC_U    ,KC_P    ,KC_QUOT ,KC_DEL  , \
CMD_T(KC_ESC) ,KC_W     ,KC_I    ,KC_S    ,KC_A    ,KC_G    ,KC_Y    ,KC_E    ,KC_T    ,KC_H    ,KC_B    ,KC_SCLN ,KC_ENT  , \
		  KC_LSFT ,KC_Z     ,KC_X    ,KC_V    ,KC_C    ,KC_L    ,KC_M    ,KC_O    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_LBRC ,KC_UP   ,KC_RBRC, \
		  KC_LCTL ,KC_LCMD  ,MO(_LOWER)       ,LSFT_T(KC_SPC)   ,LSFT_T(KC_ENT)   ,MO(_RAISE)       ,KC_LALT ,KC_LEFT ,KC_DOWN ,KC_RGHT
  ),

  [_LOWER] = LAYOUT(
//            ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	    XXXXXXX ,KC_F1    ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_SLSH ,KC_7    ,KC_8    ,KC_9    ,KC_MINS ,XXXXXXX ,XXXXXXX , \
   LWIN(KC_E) ,XXXXXXX  ,KC_LBRC ,KC_LCBR ,KC_LPRN ,KC_LT   ,KC_ASTR ,KC_4    ,KC_5    ,KC_6    ,KC_PLUS ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,XXXXXXX  ,KC_RBRC ,KC_RCBR ,KC_RPRN ,KC_GT   ,KC_0    ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,XXXXXXX ,KC_PGUP ,XXXXXXX , \
		  _______ ,_______  ,_______          ,_______          ,_______         ,_______           ,_______ ,KC_HOME ,KC_PGDN ,KC_END
  ),

  [_RAISE] = LAYOUT(
//            ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	    XXXXXXX ,KC_F1    ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_INS  , \
      XXXXXXX ,KC_TILD  ,KC_AT   ,KC_HASH ,KC_DLR  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_HOME ,KC_UP   ,KC_END  ,KC_DEL  ,KC_PIPE , \
      XXXXXXX ,KC_CIRC  ,KC_AMPR ,KC_QUES ,KC_PERC ,KC_INT3  ,XXXXXXX ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,KC_GRV   ,KC_PIPE ,KC_EXLM ,KC_UNDS ,LALT(KC_INT3),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX ,KC_PGUP ,XXXXXXX , \
	    _______ ,_______   ,_______          ,_______          ,_______         ,_______          ,_______ ,XXXXXXX ,KC_PGDN ,XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
//            ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	    XXXXXXX ,XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,EE_CLR   ,QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,NG_TAYO ,NGSW_WIN,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,XXXXXXX  ,KC_SLEP ,XXXXXXX ,XXXXXXX ,XXXXXXX ,NG_KOTI ,NGSW_MAC,NG_MLV  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , \
      XXXXXXX ,XXXXXXX  ,KC_WAKE ,XXXXXXX ,XXXXXXX ,XXXXXXX ,NG_SHOS ,NGSW_LNX,XXXXXXX, XXXXXXX, XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX, \
		  _______ ,_______  ,_______          ,_______          ,_______          ,_______          ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX
  ),

  [_NAGINATA] = LAYOUT(
//            ,         ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,        ,
	    _______ ,_______  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ , \
		  _______ ,NG_Q     ,NG_W    ,NG_E    ,NG_R    ,NG_T    ,NG_Y    ,NG_U    ,NG_I    ,NG_O    ,NG_P    ,_______ ,_______ , \
      _______ ,NG_A     ,NG_S    ,NG_D    ,NG_F    ,NG_G    ,NG_H    ,NG_J    ,NG_K    ,NG_L    ,NG_SCLN ,_______ ,_______ , \
		  _______ ,NG_Z     ,NG_X    ,NG_C    ,NG_V    ,NG_B    ,NG_N    ,NG_M    ,NG_COMM ,NG_DOT  ,NG_SLSH ,_______ ,_______ ,_______ , \
		  _______ ,_______  ,_______          ,NG_SHFT          ,NG_SHFT2         ,_______          ,_______ ,_______ ,_______ ,_______
  ),

};

uint32_t kanaoff(uint32_t trigger_time, void *cb_arg) {
  if (naginata_state())
    naginata_off();
  return NAGINATA_TIMEOUT;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  extend_deferred_exec(my_token, NAGINATA_TIMEOUT);

  switch (keycode) {
    case EISUON:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
      }
      return false;
      break;
    case KANAON:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
      }
      return false;
      break;
  }

  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  // if (!twpair_on_jis(keycode, record))
  //   return false;

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void keyboard_post_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_Y, KC_E};
  uint16_t ngoffkeys[] = {KC_A, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
  
  wait_ms(400);
  switch (detected_host_os()) {
    case OS_WINDOWS:
      layer_move(_WIN);
      switchOS(NG_WIN);
      break;
    case OS_MACOS:
    case OS_IOS:
      layer_move(_MAC);
      switchOS(NG_MAC);
      break;
    case OS_LINUX:
      layer_move(_WIN);
      switchOS(NG_LINUX);
      break;
    default:
      layer_move(_WIN);
      switchOS(NG_WIN);
  }

  my_token = defer_exec(NAGINATA_TIMEOUT, kanaoff, NULL);
}
