#include QMK_KEYBOARD_H
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _EUCALYN 0
#define _NICOLA  1 // 親指シフトレイヤー on EUCALYN
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EUCALYN,
  NICOLA,
  LOWER,
  RAISE,
  ADJUST,
  NLSHFT, // 親指シフトキー
  NRSHFT,
  EISU, KANA
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_EUCALYN] = LAYOUT( \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_BSPC, \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
    KC_TAB,   KC_Q,   KC_W,KC_COMM, KC_DOT,KC_SCLN,                      KC_M,   KC_R,   KC_D,   KC_Y,   KC_P, KC_ENT, \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   KC_LCTL,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U,                      KC_G,   KC_T,   KC_K,   KC_S,   KC_N,KC_RCTL, \
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
   KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F,KC_LCTL,   KC_RALT,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,KC_RALT, \
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
                   KC_LGUI,   EISU,  LOWER,KC_LSFT, KC_SPC,    KC_ENT,KC_RSFT,  RAISE,   KANA,KC_RGUI \
//                +-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+
),

[_NICOLA] = LAYOUT( \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_BSPC, \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
    KC_TAB,   KC_Q,   KC_W,KC_COMM, KC_DOT,KC_SCLN,                      KC_M,   KC_R,   KC_D,   KC_Y,   KC_P, KC_ENT, \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   KC_LCTL,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U,                      KC_G,   KC_T,   KC_K,   KC_S,   KC_N,KC_RCTL, \
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
   KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F,KC_LCTL,   KC_RALT,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,KC_RALT, \
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
                   KC_LGUI,   EISU,  LOWER, NLSHFT, KC_SPC,    KC_ENT, NRSHFT,  RAISE,   KANA,KC_RGUI \
//                +-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+
),

[_LOWER] = LAYOUT( \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   _______,_______,_______,_______,_______,_______,                   _______,_______,_______,_______,_______, KC_DEL,
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
//              !       @       #       $       %                          *                               +       
   _______,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,                   KC_ASTR,   KC_7,   KC_8,   KC_9,KC_PLUS,_______,\
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
//             ^      &      '      "      ~                               /                               -       
   EUCALYN,KC_CIRC,KC_AMPR,KC_QUOT,KC_DQUO,KC_TILD,                   KC_SLSH,   KC_4,   KC_5,   KC_6,KC_MINS,EUCALYN,\
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
//              \       |       `       _       \                                                          =                           
    NICOLA,KC_BSLS,KC_PIPE, KC_GRV,KC_UNDS,KC_JYEN,_______,   _______,   KC_0,   KC_1,   KC_2,   KC_3, KC_EQL, NICOLA,\
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
                   KC_LGUI,   EISU,  LOWER, NLSHFT, KC_SPC,    KC_ENT, NRSHFT,  RAISE,   KANA,KC_RGUI\
//                +-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+
),

[_RAISE] = LAYOUT( \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   _______,_______,_______,_______,_______,_______,                   _______,_______,_______,_______,_______, KC_DEL,
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   XXXXXXX,XXXXXXX,XXXXXXX,  KC_LT,  KC_GT,XXXXXXX,                   XXXXXXX,XXXXXXX,  KC_UP,XXXXXXX,KC_PGUP,XXXXXXX,
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   EUCALYN,KC_LPRN,KC_RPRN,KC_LCBR,KC_RCBR,XXXXXXX,                   XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,EUCALYN,
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
    NICOLA,XXXXXXX,XXXXXXX,KC_LBRC,KC_RBRC,XXXXXXX,XXXXXXX,   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, NICOLA,
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
                   KC_LGUI,   EISU,  LOWER,KC_LSFT, KC_SPC,    KC_ENT,KC_RSFT,  RAISE,   KANA,KC_RGUI\
//                +-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+
),

[_ADJUST] = LAYOUT( \
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   XXXXXXX,XXXXXXX,KC_WAKE,XXXXXXX,  RESET,XXXXXXX,                   XXXXXXX,XXXXXXX,KC_VOLU,XXXXXXX,KC_BRIU,XXXXXXX,
//+-------+-------+-------+-------+-------+-------+                  +-------+-------+-------+-------+-------+-------+
   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   XXXXXXX,KC_MRWD,KC_VOLD,KC_MFFD,KC_BRID,XXXXXXX,
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
   XXXXXXX,XXXXXXX,KC_SLEP,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   XXXXXXX,XXXXXXX,XXXXXXX,KC_MPLY,XXXXXXX,XXXXXXX,XXXXXXX,
//+-------+-------+-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+-------+-------+
                   KC_LGUI,   EISU,  LOWER,KC_LSFT, KC_SPC,    KC_ENT,KC_RSFT,  RAISE,   KANA,KC_RGUI\
//                +-------+-------+-------+-------+-------+  +-------+-------+-------+-------+-------+
),

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
  [KC_SLSH] = {.t = "/",  .l = "",    .r = "lo"}, 
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EUCALYN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_EUCALYN);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        layer_off(_NICOLA);
        register_code(KC_LANG2); // Mac
        // register_code(KC_MHEN); // Win
        is_nicola = false;
      } else {
        unregister_code(KC_LANG2); // Mac
        // unregister_code(KC_MHEN); // Win
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        layer_on(_NICOLA);
        register_code(KC_LANG1); // Mac
        // register_code(KC_HENK); // Win
        is_nicola = true;
      } else {
        unregister_code(KC_LANG1); // Mac
        // unregister_code(KC_HENK); // Win
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
