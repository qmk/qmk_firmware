/* Copyright 2019 eswai
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
#include"keymap_japanese.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EUCALYN,
  NLSHFT, // 親指シフトキー
  NRSHFT,
  RAISE, LOWER, ADJUST,
  CK_LPRN,
  CK_LCBR,
  CK_LBRC,
  RGBRST,
  NUMLOC
};

// Tap dance
enum {
  FUNC
};

// Layers
#define _EUCALYN  0 // default layer
#define _EUCALYNMAC  1
#define _QWERTY   2
#define _NICOLA   5 // 親指シフトレイヤー
#define _NUMPAD   6
#define _LOWER   10
#define _RAISE   11
#define _ADJUST  12

#define _____   KC_TRNS
#define XXXXX   KC_NO
#define KFUNC   TD(FUNC)
#define ALTSPC  ALT_T(KC_SPC)
#define CMDSPC  CMD_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EUCALYN] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     KC_TAB,   KC_Q,   KC_W,KC_COMM, KC_DOT,KC_SCLN,JP_MINS, JP_EQL,   KC_M,   KC_R,   KC_D,   KC_Y,   KC_P,KC_BSPC, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LCTL,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U,CK_LPRN,JP_RPRN,   KC_G,   KC_T,   KC_K,   KC_S,   KC_N,KC_RCTL, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F, JP_GRV,JP_QUOT,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,KC_RALT, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     NUMLOC,  KFUNC,  KC_F2,  KC_F5,  LOWER,KC_LSFT, ALTSPC, CTLENT,KC_RSFT,  RAISE,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT  \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_EUCALYNMAC] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     KC_TAB,   KC_Q,   KC_W,KC_COMM, KC_DOT,KC_SCLN,KC_MINS, KC_EQL,   KC_M,   KC_R,   KC_D,   KC_Y,   KC_P,KC_BSPC, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LCTL,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U,CK_LPRN,KC_RPRN,   KC_G,   KC_T,   KC_K,   KC_S,   KC_N,KC_RCTL, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F, KC_GRV,KC_QUOT,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,KC_RALT, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     NUMLOC,  KFUNC,  KC_F2,  KC_F5,  LOWER,KC_LSFT, CMDSPC, CTLENT,KC_RSFT,  RAISE,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT  \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NICOLA] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____, NLSHFT,  _____,  _____, NRSHFT,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_RAISE] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                               <       >       :       
      XXXXX,  XXXXX,  XXXXX,  KC_LT,  KC_GT,JP_COLN,JP_UNDS,JP_PLUS,  XXXXX,KC_PGUP,  KC_UP,  XXXXX,  XXXXX, KC_DEL,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               (       )       {       }                                                                   
      XXXXX,CK_LPRN,JP_RPRN,CK_LCBR,JP_RCBR,  XXXXX,JP_LCBR,JP_RCBR,  XXXXX,KC_LEFT,KC_DOWN,KC_RGHT,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                               [       ]                                                     
      XXXXX,  XXXXX,  XXXXX,CK_LBRC,JP_RBRC,  XXXXX,JP_TILD, JP_DQUO,  XXXXX,KC_PGDN,  XXXXX,  XXXXX,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_LOWER] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                !       @       #       $       %                               /                               -       
     KC_ESC,JP_EXLM,  JP_AT,JP_HASH, JP_DLR,JP_PERC,JP_BSLS,JP_PLUS,JP_SLSH,   KC_7,   KC_8,   KC_9,JP_MINS, KC_DEL,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               ^       &       '       "       ~                               *                               +       
      XXXXX,JP_CIRC,JP_AMPR,JP_QUOT, JP_DQUO,JP_TILD,JP_LBRC,JP_RBRC,JP_ASTR,   KC_4,   KC_5,   KC_6,JP_PLUS, KC_ENT,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                       |       `       _       ¥                                                               .
      XXXXX,  XXXXX,JP_PIPE, JP_GRV,JP_UNDS,JP_BSLS,JP_TILD, JP_DQUO,   KC_0,   KC_1,   KC_2,   KC_3, KC_DOT,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,KC_LWIN, KC_APP,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NUMPAD] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     KC_ESC,  XXXXX,  XXXXX,KC_COMM, KC_DOT,JP_PERC,JP_MINS,JP_PLUS,JP_SLSH,   KC_7,   KC_8,   KC_9,JP_MINS,KC_BSPC,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,JP_LPRN,JP_RPRN,JP_ASTR,   KC_4,   KC_5,   KC_6,JP_PLUS, KC_ENT,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX, KC_DOT,KC_COMM,   KC_0,   KC_1,   KC_2,   KC_3, KC_DOT, JP_EQL,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_ADJUST] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_HUI,RGB_HUD,KC_WAKE,  XXXXX,  RESET,  DF(_EUCALYN),KC_BRIU,RGB_TOG,KC_MYCM,  XXXXX,KC_WSCH,  XXXXX, KC_PWR,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_SAI,RGB_SAD,  XXXXX,  XXXXX,  XXXXX,  DF(_EUCALYNMAC),KC_BRID,RGB_MOD,KC_MAIL,KC_WBAK,KC_WHOM,KC_WFWD,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_VAI,RGB_VAD,KC_SLEP,KC_CALC,  XXXXX,  XXXXX, RGBRST,RGB_RMOD, XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

};

void dance_func_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count > 1) {
    register_code (KC_LCTRL);
    register_code (KC_LALT);
    register_code (KC_DEL);
  } else {
    register_code (KC_LCTRL);
    register_code (KC_S);
  }
}

void dance_func_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count > 1) {
    unregister_code (KC_LCTRL);
    unregister_code (KC_LALT);
    unregister_code (KC_DEL);
  } else {
    unregister_code (KC_LCTRL);
    unregister_code (KC_S);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [FUNC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_func_finished, dance_func_reset)
};

// 親指シフト
static bool is_nicola = false; // 親指シフトモードかどうか
static uint8_t ncl_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static uint8_t ncl_keycount = 0; // シフトキーも含めた入力のカウンタ
static bool ncl_rshift = false; // 右シフトキーの状態  
static bool ncl_lshift = false; // 左シフトキーの状態
static bool is_modifier = false; // modifierの状態

// 文字入力バッファ
static uint16_t ninputs[5];

// NICOLA配列のテーブル
typedef struct {
  char t[4]; // 単独
  char l[4]; // 左シフト
  char r[4]; // 右シフト
} ncl_keymap;

// NICOLA on QWERTY
/*
const ncl_keymap nmap[] = {
  [KC_Q]    = {.t = ".",  .l = "la",  .r = ""},   
  [KC_W]    = {.t = "ka", .l = "e",   .r = "ga"}, 
  [KC_E]    = {.t = "ta", .l = "ri",  .r = "da"}, 
  [KC_R]    = {.t = "ko", .l = "lya", .r = "go"}, 
  [KC_T]    = {.t = "sa", .l = "re",  .r = "za"}, 

  [KC_Y]    = {.t = "ra", .l = "pa",  .r = "yo"}, 
  [KC_U]    = {.t = "ti", .l = "di",  .r = "ni"}, 
  [KC_I]    = {.t = "ku", .l = "gu",  .r = "ru"}, 
  [KC_O]    = {.t = "tu", .l = "du",  .r = "ma"}, 
  [KC_P]    = {.t = ",",  .l = "pi",  .r = "le"}, 

  [KC_A]    = {.t = "u",  .l = "wo",  .r = "vu"},
  [KC_S]    = {.t = "si", .l = "a",   .r = "zi"}, 
  [KC_D]    = {.t = "te", .l = "na",  .r = "de"}, 
  [KC_F]    = {.t = "ke", .l = "lyu", .r = "ge"}, 
  [KC_G]    = {.t = "se", .l = "mo",  .r = "ze"}, 

  [KC_H]    = {.t = "ha", .l = "ba",  .r = "mi"}, 
  [KC_J]    = {.t = "to", .l = "do",  .r = "o"},  
  [KC_K]    = {.t = "ki", .l = "gi",  .r = "no"}, 
  [KC_L]    = {.t = "i",  .l = "po",  .r = "lyo"},
  [KC_SCLN] = {.t = "nn", .l = "",    .r = "ltu"},

  [KC_Z]    = {.t = ".",  .l = "lu",  .r = ""},   
  [KC_X]    = {.t = "hi", .l = "-",   .r = "bi"}, 
  [KC_C]    = {.t = "su", .l = "ro",  .r = "zu"}, 
  [KC_V]    = {.t = "hu", .l = "ya",  .r = "bu"}, 
  [KC_B]    = {.t = "he", .l = "li",  .r = "be"}, 

  [KC_N]    = {.t = "me", .l = "pu",  .r = "nu"}, 
  [KC_M]    = {.t = "so", .l = "zo",  .r = "yu"}, 
  [KC_COMM] = {.t = "ne", .l = "pe",  .r = "mu"}, 
  [KC_DOT]  = {.t = "ho", .l = "bo",  .r = "wa"}, 
  [KC_SLSH] = {.t = "/",  .l = "?",    .r = "lo"}, 
};
*/

// NICOLA on EUCALYN
const ncl_keymap nmap[] = {
  [KC_Q]    = {.t = ".",  .l = "la",  .r = ""},   
  [KC_W]    = {.t = "ka", .l = "e",   .r = "ga"}, 
  [KC_COMM] = {.t = "ta", .l = "ri",  .r = "da"}, 
  [KC_DOT]  = {.t = "ko", .l = "lya", .r = "go"}, 
  [KC_SCLN] = {.t = "sa", .l = "re",  .r = "za"}, 

  [KC_M]    = {.t = "ra", .l = "pa",  .r = "yo"}, 
  [KC_R]    = {.t = "ti", .l = "di",  .r = "ni"}, 
  [KC_D]    = {.t = "ku", .l = "gu",  .r = "ru"}, 
  [KC_Y]    = {.t = "tu", .l = "du",  .r = "ma"}, 
  [KC_P]    = {.t = ",",  .l = "pi",  .r = "le"}, 

  [KC_A]    = {.t = "u",  .l = "wo",  .r = "vu"},
  [KC_O]    = {.t = "si", .l = "a",   .r = "zi"}, 
  [KC_E]    = {.t = "te", .l = "na",  .r = "de"}, 
  [KC_I]    = {.t = "ke", .l = "lyu", .r = "ge"}, 
  [KC_U]    = {.t = "se", .l = "mo",  .r = "ze"}, 

  [KC_G]    = {.t = "ha", .l = "ba",  .r = "mi"}, 
  [KC_T]    = {.t = "to", .l = "do",  .r = "o"},  
  [KC_K]    = {.t = "ki", .l = "gi",  .r = "no"}, 
  [KC_S]    = {.t = "i",  .l = "po",  .r = "lyo"},
  [KC_N]    = {.t = "nn", .l = "",    .r = "ltu"},

  [KC_Z]    = {.t = ".",  .l = "lu",  .r = ""},   
  [KC_X]    = {.t = "hi", .l = "-",   .r = "bi"}, 
  [KC_C]    = {.t = "su", .l = "ro",  .r = "zu"}, 
  [KC_V]    = {.t = "hu", .l = "ya",  .r = "bu"}, 
  [KC_F]    = {.t = "he", .l = "li",  .r = "be"}, 

  [KC_B]    = {.t = "me", .l = "pu",  .r = "nu"}, 
  [KC_H]    = {.t = "so", .l = "zo",  .r = "yu"}, 
  [KC_J]    = {.t = "ne", .l = "pe",  .r = "mu"}, 
  [KC_L]    = {.t = "ho", .l = "bo",  .r = "wa"}, 
  [KC_SLSH] = {.t = "/",  .l = "?",    .r = "lo"}, 
};

void ncl_type(void);
void ncl_clear(void);

// シフトキーの状態に応じて文字をPCへ送る
void ncl_type(void) {
  for (int i = 0; i < ncl_chrcount; i++) {
    if (ninputs[i] == 0) break;
    if (ncl_lshift) {
      send_string(nmap[ninputs[i]].l);
    } else if (ncl_rshift) {
      send_string(nmap[ninputs[i]].r);
    } else {
      send_string(nmap[ninputs[i]].t);
    }
  }
  ncl_clear();
}

// バッファをクリアする
void ncl_clear(void) {
  for (int i = 0; i < 5; i++) {
    ninputs[i] = 0;
  }
  ncl_chrcount = 0;
  ncl_keycount = 0;
  ncl_lshift = false;
  ncl_rshift = false;
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void update_led(void);

void update_led() {
  if (layer_state_is(_NUMPAD)) {
    rgblight_setrgb_at(5, 5, 20, 3);
  }
  if (layer_state_is(_NUMPAD) || layer_state_is(_LOWER)) {
    rgblight_setrgb_at(5, 5, 20, 37);
    rgblight_setrgb_at(5, 5, 20, 38);
    rgblight_setrgb_at(5, 5, 20, 39);
    rgblight_setrgb_at(5, 5, 20, 40);
    rgblight_setrgb_at(5, 5, 20, 41);
    rgblight_setrgb_at(5, 5, 20, 42);
    rgblight_setrgb_at(5, 5, 20, 45);
    rgblight_setrgb_at(5, 5, 20, 46);
    rgblight_setrgb_at(5, 5, 20, 47);
  }
  if (layer_state_is(_RAISE)) {
    rgblight_setrgb_at(15, 2, 5, 38);
    rgblight_setrgb_at(15, 2, 5, 40);
    rgblight_setrgb_at(15, 2, 5, 41);
    rgblight_setrgb_at(15, 2, 5, 46);
  }
  if (!layer_state_is(_NUMPAD) && !layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_setrgb_range(0, 0, 0, 0, 55);
  }
  if (is_nicola) {
    rgblight_setrgb_range(10, 10, 10, 56, 71);
  } else {
    rgblight_setrgb_range(0, 0, 0, 56, 71);
  }
}

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case NUMLOC:
      if (record->event.pressed) {
        layer_invert(_NUMPAD);
      }
      update_led();
      return false;
      break;
    case RGBRST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
      }
      update_led();
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      update_led();
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        if (raise_pressed) {
          raise_pressed = false;
        } else {
          lower_pressed = true;
        }
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (lower_pressed) {
          layer_off(_NICOLA);
          register_code(KC_LANG2); // Mac
          register_code(KC_MHEN); // Win
          is_nicola = false;
          unregister_code(KC_LANG2); // Mac
          unregister_code(KC_MHEN); // Win
          lower_pressed = false;
        }
      }
      update_led();
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        if (lower_pressed) {
          lower_pressed = false;
        } else {
          raise_pressed = true;
        }
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (raise_pressed) {
          layer_on(_NICOLA);
          register_code(KC_LANG1); // Mac
          register_code(KC_HENK); // Win
          is_nicola = true;
          unregister_code(KC_LANG1); // Mac
          unregister_code(KC_HENK); // Win
          raise_pressed = false;
        }
      }
      update_led();
      return false;
      break;
    default:
      lower_pressed = false;
      raise_pressed = false;
  }

  switch (keycode) {
    case CK_LPRN:
      if (record->event.pressed) {
        register_code(KC_LSHIFT);
        register_code(KC_8);
        unregister_code(KC_8);
        register_code(KC_9);
        unregister_code(KC_9);
        unregister_code(KC_LSHIFT);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
      }
      return false;
      break;
    case CK_LCBR:
      if (record->event.pressed) {
        register_code(KC_LSHIFT);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        register_code(KC_NUHS);
        unregister_code(KC_NUHS);
        unregister_code(KC_LSHIFT);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
      }
      return false;
      break;
    case CK_LBRC:
      if (record->event.pressed) {
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        register_code(KC_NUHS);
        unregister_code(KC_NUHS);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
      }
      return false;
      break;
  }

  // 親指シフトの処理　ここから

  // modifierが押されているか
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
    case LOWER:
    case RAISE:
    case ADJUST:
      if (record->event.pressed) {
        is_modifier = true;
      } else {
        is_modifier = false;
      }
      break;
  }

  if (is_nicola & !is_modifier) {
    if (record->event.pressed) {
      switch (keycode) {
        case NLSHFT: // 親指シフトキー
          ncl_lshift = true;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        case NRSHFT:
          ncl_rshift = true;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          ninputs[ncl_chrcount] = keycode;
          ncl_chrcount++;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        default: // 親指シフトに関係ないキー
          ncl_clear();
          break;
      }

    } else { // key release
      switch (keycode) {
        case NLSHFT: // 親指シフトキー
          ncl_lshift = false;
          if (ncl_keycount > 0) ncl_type();
          return false;
          break;
        case NRSHFT:
          ncl_rshift = false;
          if (ncl_keycount > 0) ncl_type();
          return false;
          break; 
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          if (ncl_keycount > 0) ncl_type();
          return false;
          break;
      }
    }
  }
  // 親指シフト処理 ここまで

  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
