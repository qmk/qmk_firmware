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
  NUMLOC,
  UNDGL,
  KANA,
  EISU
};

// Layers
enum kepmap_layers {
  _EUCALYN,
  _SHIFT,
  _NICOLA,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define _____   KC_TRNS
#define XXXXX   KC_NO
#define SFTSPC  SFT_T(KC_SPC)
#define ALTENT  ALT_T(KC_ENT)
#define ALTSPC  ALT_T(KC_SPC)
#define ALTBS   ALT_T(KC_BSPC)
#define CMDSPC  CMD_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define KC(A) C(KC_##A)
#define KS(A) S(KC_##A)
#define KG(A) G(KC_##A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EUCALYN] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    JP_LPRN,   KC_Q,   KC_W,KC_COMM, KC_DOT,KC_SCLN, JP_YEN,  KC_F2,   KC_M,   KC_R,   KC_D,   KC_Y,   KC_P,JP_MINS, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    JP_RPRN,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U, KC_ESC,  KC(S),   KC_G,   KC_T,   KC_K,   KC_S,   KC_N,JP_PLUS, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     JP_GRV,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F, KC_TAB, KC_DEL,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,JP_QUOT, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LCTL, NUMLOC,KC_LALT,MO(_SHIFT),LOWER,SFTSPC, ALTBS,  CTLENT, SFTSPC,  RAISE,   KC_0, KC_DOT,KC_COMM,KC_RCTL  \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_SHIFT] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
   JP_LCBR,S(KC_Q),S(KC_W),  KC_LT, KC_GT,JP_COLN,JP_PIPE,S(KC_F2),S(KC_M),S(KC_R),S(KC_D),S(KC_Y),S(KC_P),JP_UNDS, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
   JP_RCBR,S(KC_A),S(KC_O),S(KC_E),S(KC_I),S(KC_U),S(KC_ESC),KC(S),S(KC_G),S(KC_T),S(KC_K),S(KC_S),S(KC_N),JP_EQL, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    JP_TILD,S(KC_Z),S(KC_X),S(KC_C),S(KC_V),S(KC_F),S(KC_TAB),S(KC_DEL),S(KC_B),S(KC_H),S(KC_J),S(KC_L),KC_QUES,JP_DQUO, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 S(KC_LCTL),NUMLOC,S(KC_LALT),MO(_SHIFT),LOWER,SFTSPC,S(KC_BSPC),S(KC_ENT),SFTSPC,RAISE, KC_0,KC_DOT,S(KC_RCMD),S(KC_RCTL)  \
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
    JP_LCBR,  XXXXX,  XXXXX,  KC_LT,  KC_GT,JP_COLN,  _____,  _____,  XXXXX, KS(UP),  KC_UP,  XXXXX,    XXXXX,KC_PGUP,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               (       )       {       }                                                                   
    JP_RCBR,JP_LPRN,JP_RPRN,JP_LCBR,JP_RCBR,  XXXXX,  _____,  _____,  XXXXX,KC_LEFT,KC_DOWN,KC_RGHT,  XXXXX,KC_PGDN,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                               [       ]                                                     
      XXXXX,  XXXXX,  XXXXX,JP_LBRC,JP_RBRC,  XXXXX,  _____, KC_BSPC,XXXXX,KS(LEFT),KS(DOWN),KS(RGHT), XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  KANA,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_LOWER] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                !       @       #       $       %                                                             
    JP_LBRC,JP_EXLM,  JP_AT,JP_HASH, JP_DLR,JP_PERC,  _____,  _____,JP_LPRN,JP_SLSH,   KC_7,   KC_8,   KC_9,JP_MINS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               ^       &       '       "       ~                                                              
    JP_RBRC,JP_CIRC,JP_AMPR,JP_QUOT, JP_DQUO,JP_TILD,  _____,  _____,JP_RPRN,JP_ASTR,   KC_4,   KC_5,   KC_6,JP_PLUS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                       |       `       _       ¥                                                               
      XXXXX,  XXXXX,JP_PIPE, JP_GRV,JP_UNDS,JP_BSLS,  _____,KC_BSPC,JP_PERC, JP_EQL,   KC_1,   KC_2,   KC_3, KC_ENT,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,   EISU,  _____,  _____,  _____,  _____,   KC_0, KC_DOT,KC_COMM,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NUMPAD] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                                        $       %                                                             
      _____,  _____,  _____,  KC_UP, JP_DLR,JP_PERC,  _____,  _____,JP_LPRN,JP_SLSH,   KC_7,   KC_8,   KC_9,JP_MINS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,KC_LEFT,KC_DOWN,KC_RGHT,JP_TILD,  _____,  _____,JP_RPRN,JP_ASTR,   KC_4,   KC_5,   KC_6,JP_PLUS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,JP_PERC, JP_EQL,   KC_1,   KC_2,   KC_3, KC_ENT,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____, NUMLOC,  KC_F2,  KC_F5,  _____,  _____,  _____,  _____,  _____,  _____,   KC_0, KC_DOT,KC_COMM,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_ADJUST] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_HUI,RGB_HUD,KC_WAKE,  XXXXX,  RESET,  XXXXX,KC_BRIU,RGB_TOG,KC_MYCM,  XXXXX,KC_WSCH,  XXXXX, KC_PWR,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_SAI,RGB_SAD,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_BRID,RGB_MOD,KC_MAIL,KC_WBAK,KC_WHOM,KC_WFWD,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_VAI,RGB_VAD,KC_SLEP,KC_CALC,  XXXXX,  XXXXX,RGBRST,RGB_RMOD,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      UNDGL,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

};

enum combo_events {
  LOGIN_CMB,
};

const uint16_t PROGMEM login_combo[] = {KC_B, KC_DEL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [LOGIN_CMB] = COMBO_ACTION(login_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case LOGIN_CMB:
      if (pressed) {
        register_code (KC_LCTRL);
        register_code (KC_LALT);
        register_code (KC_DEL);
        unregister_code (KC_DEL);
        unregister_code (KC_LALT);
        unregister_code (KC_LCTRL);
      }
      break;
  }
}

// 親指シフト
static bool is_nicola = false; // 親指シフトモードかどうか
static uint8_t ncl_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static uint8_t ncl_keycount = 0; // シフトキーも含めた入力のカウンタ
static bool ncl_rshift = false; // 右シフトキーの状態  
static bool ncl_lshift = false; // 左シフトキーの状態
static bool is_modifier = false; // modifierの状態
static bool underglow = false;
static bool ncl_space = false; // シフトキーかスペース入力か

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
  ncl_space = false;
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void update_led(void);

void update_led() {
  if (!layer_state_is(_NUMPAD) && !layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_sethsv_range(0, 0, 0, 0, 55);
  }
  if (!is_nicola) {
    rgblight_sethsv_at(0, 0, 0, 17);
    rgblight_sethsv_at(0, 0, 0, 38);
  }
  if (layer_state_is(_NUMPAD)) {
    rgblight_sethsv_at(150, 200, 70, 4);
    rgblight_sethsv_range(150, 200, 60, 40, 43);
    rgblight_sethsv_range(150, 200, 60, 45, 51);
    rgblight_sethsv_at(150, 200, 70, 9);
    rgblight_sethsv_at(150, 200, 70, 14);
    rgblight_sethsv_at(150, 200, 70, 15);
    rgblight_sethsv_at(150, 200, 70, 17);
  }
  if (layer_state_is(_LOWER)) {
    // rgblight_sethsv_at(240, 100, 70, 19);
    rgblight_sethsv_range(240, 200, 60, 40, 43);
    rgblight_sethsv_range(240, 200, 60, 45, 51);
  }
  if (layer_state_is(_RAISE)) {
    // rgblight_sethsv_at(100, 100, 70, 36);
    rgblight_sethsv_at(100, 255, 70, 38);
    rgblight_sethsv_at(100, 255, 70, 40);
    rgblight_sethsv_at(100, 255, 70, 41);
    rgblight_sethsv_at(100, 255, 70, 46);
  }
  if (is_nicola) {
    rgblight_sethsv_at(150, 200, 100, 17);
    rgblight_sethsv_at(150, 200, 100, 38);
    // rgblight_setrgb_range(10, 10, 10, 56, 71);
  }
  if (underglow) {
    rgblight_sethsv_range(150, 200, 200, 56, 71);
  } else {
    rgblight_sethsv_range(150, 200, 0, 56, 71);
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
    case UNDGL:
      if (record->event.pressed) {
        underglow = !underglow;
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
          is_nicola = false;
          register_code(KC_LANG2); // Mac
          unregister_code(KC_LANG2); // Mac
          register_code(KC_MHEN); // Win
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
          is_nicola = true;
          register_code(KC_LANG1); // Mac
          unregister_code(KC_LANG1); // Mac
          register_code(KC_HENK); // Win
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
          if (ncl_chrcount == 0) ncl_space = true;
          ncl_lshift = true;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        case NRSHFT:
          if (ncl_chrcount == 0) ncl_space = true;
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
          if (ncl_chrcount > 0) {
            ncl_type();
          } else if (ncl_space) {
            register_code(KC_SPC);
            unregister_code(KC_SPC);
          }
          return false;
          break;
        case NRSHFT:
          ncl_rshift = false;
          if (ncl_chrcount > 0) {
            ncl_type();
          } else if (ncl_space) {
            register_code(KC_SPC);
            unregister_code(KC_SPC);
          }
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
