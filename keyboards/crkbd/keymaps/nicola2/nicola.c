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
#include "nicola.h"

#if !defined(__AVR__)
  #include <string.h>
  #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#define NGBUFFER 5 // バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキー含む)
static bool is_nicola = false; // 親指シフトがオンかオフか
static uint8_t nicola_layer = 0; // レイヤー番号
static uint8_t n_modifier = 0; // 押しているmodifierキーの数
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

// 31キーを32bitの各ビットに割り当てる
#define B_Q    (1UL<<0)
#define B_W    (1UL<<1)
#define B_E    (1UL<<2)
#define B_R    (1UL<<3)
#define B_T    (1UL<<4)

#define B_Y    (1UL<<5)
#define B_U    (1UL<<6)
#define B_I    (1UL<<7)
#define B_O    (1UL<<8)
#define B_P    (1UL<<9)

#define B_A    (1UL<<10)
#define B_S    (1UL<<11)
#define B_D    (1UL<<12)
#define B_F    (1UL<<13)
#define B_G    (1UL<<14)

#define B_H    (1UL<<15)
#define B_J    (1UL<<16)
#define B_K    (1UL<<17)
#define B_L    (1UL<<18)
#define B_SCLN (1UL<<19)

#define B_Z    (1UL<<20)
#define B_X    (1UL<<21)
#define B_C    (1UL<<22)
#define B_V    (1UL<<23)
#define B_B    (1UL<<24)

#define B_N    (1UL<<25)
#define B_M    (1UL<<26)
#define B_COMM (1UL<<27)
#define B_DOT  (1UL<<28)
#define B_SLSH (1UL<<29)

#define B_SHFTL (1UL<<30)
#define B_SHFTR (1UL<<31)

// 文字入力バッファ
static uint16_t ninputs[NGBUFFER];

// キーコードとキービットの対応
// メモリ削減のため配列はNG_Qを0にしている
const uint32_t ng_key[] = {
  [NG_Q    - NG_Q] = B_Q,
  [NG_W    - NG_Q] = B_W,
  [NG_E    - NG_Q] = B_E,
  [NG_R    - NG_Q] = B_R,
  [NG_T    - NG_Q] = B_T,

  [NG_Y    - NG_Q] = B_Y,
  [NG_U    - NG_Q] = B_U,
  [NG_I    - NG_Q] = B_I,
  [NG_O    - NG_Q] = B_O,
  [NG_P    - NG_Q] = B_P,

  [NG_A    - NG_Q] = B_A,
  [NG_S    - NG_Q] = B_S,
  [NG_D    - NG_Q] = B_D,
  [NG_F    - NG_Q] = B_F,
  [NG_G    - NG_Q] = B_G,

  [NG_H    - NG_Q] = B_H,
  [NG_J    - NG_Q] = B_J,
  [NG_K    - NG_Q] = B_K,
  [NG_L    - NG_Q] = B_L,
  [NG_SCLN - NG_Q] = B_SCLN,

  [NG_Z    - NG_Q] = B_Z,
  [NG_X    - NG_Q] = B_X,
  [NG_C    - NG_Q] = B_C,
  [NG_V    - NG_Q] = B_V,
  [NG_B    - NG_Q] = B_B,

  [NG_N    - NG_Q] = B_N,
  [NG_M    - NG_Q] = B_M,
  [NG_COMM - NG_Q] = B_COMM,
  [NG_DOT  - NG_Q] = B_DOT,
  [NG_SLSH - NG_Q] = B_SLSH,

  [NG_SHFTL - NG_Q] = B_SHFTL,
  [NG_SHFTR - NG_Q] = B_SHFTR,
};

// 親指シフトカナ変換テーブル
typedef struct {
  uint32_t key;
  char kana[4];
} nicola_keymap;

const PROGMEM nicola_keymap ngmap[] = {
  // 単独
  {.key = B_Q               , .kana = "."},
  {.key = B_W               , .kana = "ka"},
  {.key = B_E               , .kana = "ta"},
  {.key = B_R               , .kana = "ko"},
  {.key = B_T               , .kana = "sa"},
  {.key = B_Y               , .kana = "ra"},
  {.key = B_U               , .kana = "ti"},
  {.key = B_I               , .kana = "ku"},
  {.key = B_O               , .kana = "tu"},
  {.key = B_P               , .kana = ","},

  {.key = B_A               , .kana = "u"},
  {.key = B_S               , .kana = "si"},
  {.key = B_D               , .kana = "te"},
  {.key = B_F               , .kana = "ke"},
  {.key = B_G               , .kana = "se"},
  {.key = B_H               , .kana = "ha"},
  {.key = B_J               , .kana = "to"},
  {.key = B_K               , .kana = "ki"},
  {.key = B_L               , .kana = "i"},
  {.key = B_SCLN            , .kana = "nn"},

  {.key = B_Z               , .kana = "."},
  {.key = B_X               , .kana = "hi"},
  {.key = B_C               , .kana = "su"},
  {.key = B_V               , .kana = "hu"},
  {.key = B_B               , .kana = "he"},
  {.key = B_N               , .kana = "me"},
  {.key = B_M               , .kana = "so"},
  {.key = B_COMM            , .kana = "ne"},
  {.key = B_DOT             , .kana = "ho"},
  {.key = B_SLSH            , .kana = "/"},

  // Shift and space
  // {.key = B_SHFTL           , .kana = " "},
  // {.key = B_SHFTR           , .kana = " "},

  // Shift and Henkan/Muhenkan
  // {.key = B_SHFTL           , .kana = SS_TAP(X_INT5)},
  // {.key = B_SHFTR           , .kana = SS_TAP(X_INT4)},

  // 左シフト
  {.key = B_SHFTL|B_Q       , .kana = "la"},
  {.key = B_SHFTL|B_W       , .kana = "e"},
  {.key = B_SHFTL|B_E       , .kana = "ri"},
  {.key = B_SHFTL|B_R       , .kana = "lya"},
  {.key = B_SHFTL|B_T       , .kana = "re"},
  {.key = B_SHFTL|B_Y       , .kana = "pa"},
  {.key = B_SHFTL|B_U       , .kana = "di"},
  {.key = B_SHFTL|B_I       , .kana = "gu"},
  {.key = B_SHFTL|B_O       , .kana = "du"},
  {.key = B_SHFTL|B_P       , .kana = "pi"},

  {.key = B_SHFTL|B_A       , .kana = "wo"},
  {.key = B_SHFTL|B_S       , .kana = "a"},
  {.key = B_SHFTL|B_D       , .kana = "na"},
  {.key = B_SHFTL|B_F       , .kana = "lyu"},
  {.key = B_SHFTL|B_G       , .kana = "mo"},
  {.key = B_SHFTL|B_H       , .kana = "ba"},
  {.key = B_SHFTL|B_J       , .kana = "do"},
  {.key = B_SHFTL|B_K       , .kana = "gi"},
  {.key = B_SHFTL|B_L       , .kana = "po"},
  {.key = B_SHFTL|B_SCLN    , .kana = ""},

  {.key = B_SHFTL|B_Z       , .kana = "lu"},
  {.key = B_SHFTL|B_X       , .kana = "-"},
  {.key = B_SHFTL|B_C       , .kana = "ro"},
  {.key = B_SHFTL|B_V       , .kana = "ya"},
  {.key = B_SHFTL|B_B       , .kana = "li"},
  {.key = B_SHFTL|B_N       , .kana = "pu"},
  {.key = B_SHFTL|B_M       , .kana = "zo"},
  {.key = B_SHFTL|B_COMM    , .kana = "pe"},
  {.key = B_SHFTL|B_DOT     , .kana = "bo"},
  {.key = B_SHFTL|B_SLSH    , .kana = "?"},

  // 右シフト
  {.key = B_SHFTR|B_Q       , .kana = ""},
  {.key = B_SHFTR|B_W       , .kana = "ga"},
  {.key = B_SHFTR|B_E       , .kana = "da"},
  {.key = B_SHFTR|B_R       , .kana = "go"},
  {.key = B_SHFTR|B_T       , .kana = "za"},
  {.key = B_SHFTR|B_Y       , .kana = "yo"},
  {.key = B_SHFTR|B_U       , .kana = "ni"},
  {.key = B_SHFTR|B_I       , .kana = "ru"},
  {.key = B_SHFTR|B_O       , .kana = "ma"},
  {.key = B_SHFTR|B_P       , .kana = "le"},

  {.key = B_SHFTR|B_A       , .kana = "vu"},
  {.key = B_SHFTR|B_S       , .kana = "zi"},
  {.key = B_SHFTR|B_D       , .kana = "de"},
  {.key = B_SHFTR|B_F       , .kana = "ge"},
  {.key = B_SHFTR|B_G       , .kana = "ze"},
  {.key = B_SHFTR|B_H       , .kana = "mi"},
  {.key = B_SHFTR|B_J       , .kana = "o"},
  {.key = B_SHFTR|B_K       , .kana = "no"},
  {.key = B_SHFTR|B_L       , .kana = "lyo"},
  {.key = B_SHFTR|B_SCLN    , .kana = "ltu"},

  {.key = B_SHFTR|B_Z       , .kana = ""},
  {.key = B_SHFTR|B_X       , .kana = "bi"},
  {.key = B_SHFTR|B_C       , .kana = "zu"},
  {.key = B_SHFTR|B_V       , .kana = "bu"},
  {.key = B_SHFTR|B_B       , .kana = "be"},
  {.key = B_SHFTR|B_N       , .kana = "nu"},
  {.key = B_SHFTR|B_M       , .kana = "yu"},
  {.key = B_SHFTR|B_COMM    , .kana = "mu"},
  {.key = B_SHFTR|B_DOT     , .kana = "wa"},
  {.key = B_SHFTR|B_SLSH    , .kana = "lo"},

};

// 親指シフトのレイヤー、シフトキーを設定
void set_nicola(uint8_t layer) {
  nicola_layer = layer;
}

// 親指シフトをオンオフ
void nicola_on(void) {
  is_nicola = true;
  keycomb = 0UL;
  nicola_clear();
  layer_on(nicola_layer);

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

void nicola_off(void) {
  is_nicola = false;
  keycomb = 0UL;
  nicola_clear();
  layer_off(nicola_layer);

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 親指シフトの状態
bool nicola_state(void) {
  return is_nicola;
}

// キー入力を文字に変換して出力する
void nicola_type(void) {
  nicola_keymap bngmap; // PROGMEM buffer

  bool douji = false; // 同時押しか連続押しか
  uint32_t skey = 0; // 連続押しの場合のバッファ

  switch (keycomb) {
    // send_stringできないキー、長すぎるマクロはここで定義
    // case B_F|B_G:
    //   nicola_off();
    //   break;
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合 ngmapに定義されている
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb == bngmap.key) {
          douji = true;
          send_string(bngmap.kana);
          break;
        }
      }
      // 連続押しの場合 ngmapに定義されていない
      if (!douji) {
        for (int j = 0; j < ng_chrcount; j++) {
          skey = ng_key[ninputs[j] - NG_Q];
          if ((keycomb & B_SHFTL) > 0) skey |= B_SHFTL; // シフトキー状態を反映
          if ((keycomb & B_SHFTR) > 0) skey |= B_SHFTR; // シフトキー状態を反映
          for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
            memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
            if (skey == bngmap.key) {
              send_string(bngmap.kana);
              break;
            }
          }
        }
      }
  }

  nicola_clear(); // バッファを空にする
}

// バッファをクリアする
void nicola_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
  #ifndef NICOLA_RENZOKU // 連続シフト、シフト押しっぱなしで入力可能
    keycomb = 0UL;
  #endif
}

// 入力モードか編集モードかを確認する
void nicola_mode(uint16_t keycode, keyrecord_t *record) {
  if (!is_nicola) return;

  // modifierが押されたらレイヤーをオフ
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
      if (record->event.pressed) {
        n_modifier++;
        layer_off(nicola_layer);
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(nicola_layer);
        }
      }
      break;
  }

}

// 親指シフトの入力処理
bool process_nicola(uint16_t keycode, keyrecord_t *record) {
  // if (!is_nicola || n_modifier > 0) return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_Q ... NG_SHFTR:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // 2文字押したら処理を開始
        if (ng_chrcount > 1) {
          nicola_type();
        }
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFTR:
        // 2文字入力していなくても、どれかキーを離したら処理を開始する
        if (ng_chrcount > 0) {
          nicola_type();
        }
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        return false;
        break;
    }
  }
  return true;
}

