/* Copyright 2018-2022 eswai <@eswai>
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
#include "naginata.h"

#include <string.h>

#define NGBUFFER 10 // キー入力バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。
static uint16_t ngon_keys[2]; // 薙刀式をオンにするキー(通常HJ)
static uint16_t ngoff_keys[2]; // 薙刀式をオフにするキー(通常FG)
static bool is_henshu = false; // 編集モードかどうか

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

#define B_SHFT (1UL<<30)

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

  [NG_SHFT - NG_Q] = B_SHFT,
  [NG_SHFT2 - NG_Q] = B_SHFT,
};

// カナ変換テーブル
typedef struct {
  uint32_t key;
  char kana[6];
} naginata_keymap;

const PROGMEM naginata_keymap ngmap[] = {
  // 清音
  {.key = B_J                      , .kana = "a"       }, // あ
  {.key = B_K                      , .kana = "i"       }, // い
  {.key = B_L                      , .kana = "u"       }, // う
  {.key = B_SHFT|B_O               , .kana = "e"       }, // え
  {.key = B_SHFT|B_N               , .kana = "o"       }, // お
  {.key = B_F                      , .kana = "ka"      }, // か
  {.key = B_W                      , .kana = "ki"      }, // き
  {.key = B_H                      , .kana = "ku"      }, // く
  {.key = B_S                      , .kana = "ke"      }, // け
  {.key = B_V                      , .kana = "ko"      }, // こ
  {.key = B_SHFT|B_U               , .kana = "sa"      }, // さ
  {.key = B_R                      , .kana = "si"      }, // し
  {.key = B_O                      , .kana = "su"      }, // す
  {.key = B_SHFT|B_A               , .kana = "se"      }, // せ
  {.key = B_B                      , .kana = "so"      }, // そ
  {.key = B_N                      , .kana = "ta"      }, // た
  {.key = B_SHFT|B_G               , .kana = "ti"      }, // ち
  {.key = B_SHFT|B_L               , .kana = "tu"      }, // つ
  {.key = B_E                      , .kana = "te"      }, // て
  {.key = B_D                      , .kana = "to"      }, // と
  {.key = B_M                      , .kana = "na"      }, // な
  {.key = B_SHFT|B_D               , .kana = "ni"      }, // に
  {.key = B_SHFT|B_W               , .kana = "nu"      }, // ぬ
  {.key = B_SHFT|B_R               , .kana = "ne"      }, // ね
  {.key = B_SHFT|B_J               , .kana = "no"      }, // の
  {.key = B_C                      , .kana = "ha"      }, // は
  {.key = B_X                      , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_X               , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_SCLN            , .kana = "hu"      }, // ふ
  {.key = B_P                      , .kana = "he"      }, // へ
  {.key = B_Z                      , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_Z               , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_F               , .kana = "ma"      }, // ま
  {.key = B_SHFT|B_B               , .kana = "mi"      }, // み
  {.key = B_SHFT|B_COMM            , .kana = "mu"      }, // む
  {.key = B_SHFT|B_S               , .kana = "me"      }, // め
  {.key = B_SHFT|B_K               , .kana = "mo"      }, // も
  {.key = B_SHFT|B_H               , .kana = "ya"      }, // や
  {.key = B_SHFT|B_P               , .kana = "yu"      }, // ゆ
  {.key = B_SHFT|B_I               , .kana = "yo"      }, // よ
  {.key = B_DOT                    , .kana = "ra"      }, // ら
  {.key = B_SHFT|B_E               , .kana = "ri"      }, // り
  {.key = B_I                      , .kana = "ru"      }, // る
  {.key = B_SLSH                   , .kana = "re"      }, // れ
  {.key = B_SHFT|B_SLSH            , .kana = "re"      }, // れ
  {.key = B_A                      , .kana = "ro"      }, // ろ
  {.key = B_SHFT|B_DOT             , .kana = "wa"      }, // わ
  {.key = B_SHFT|B_C               , .kana = "wo"      }, // を
  {.key = B_COMM                   , .kana = "nn"      }, // ん
  {.key = B_SCLN                   , .kana = "-"       }, // ー

  // 濁音
  {.key = B_J|B_F                  , .kana = "ga"      }, // が
  {.key = B_J|B_W                  , .kana = "gi"      }, // ぎ
  {.key = B_F|B_H                  , .kana = "gu"      }, // ぐ
  {.key = B_J|B_S                  , .kana = "ge"      }, // げ
  {.key = B_J|B_V                  , .kana = "go"      }, // ご
  {.key = B_F|B_U                  , .kana = "za"      }, // ざ
  {.key = B_J|B_R                  , .kana = "zi"      }, // じ
  {.key = B_F|B_O                  , .kana = "zu"      }, // ず
  {.key = B_J|B_A                  , .kana = "ze"      }, // ぜ
  {.key = B_J|B_B                  , .kana = "zo"      }, // ぞ
  {.key = B_F|B_N                  , .kana = "da"      }, // だ
  {.key = B_J|B_G                  , .kana = "di"      }, // ぢ
  {.key = B_F|B_L                  , .kana = "du"      }, // づ
  {.key = B_J|B_E                  , .kana = "de"      }, // で
  {.key = B_J|B_D                  , .kana = "do"      }, // ど
  {.key = B_J|B_C                  , .kana = "ba"      }, // ば
  {.key = B_J|B_X                  , .kana = "bi"      }, // び
  {.key = B_F|B_SCLN               , .kana = "bu"      }, // ぶ
  {.key = B_F|B_P                  , .kana = "be"      }, // べ
  {.key = B_J|B_Z                  , .kana = "bo"      }, // ぼ
  {.key = B_Q                      , .kana = "vu"      }, // ゔ

  // 半濁音
  {.key = B_M|B_C                  , .kana = "pa"      }, // ぱ
  {.key = B_M|B_X                  , .kana = "pi"      }, // ぴ
  {.key = B_V|B_SCLN               , .kana = "pu"      }, // ぷ
  {.key = B_V|B_P                  , .kana = "pe"      }, // ぺ
  {.key = B_M|B_Z                  , .kana = "po"      }, // ぽ

  // 小書き
  {.key = B_Q|B_H                  , .kana = "xya"     }, // ゃ
  {.key = B_Q|B_P                  , .kana = "xyu"     }, // ゅ
  {.key = B_Q|B_I                  , .kana = "xyo"     }, // ょ
  {.key = B_Q|B_J                  , .kana = "xa"      }, // ぁ
  {.key = B_Q|B_K                  , .kana = "xi"      }, // ぃ
  {.key = B_Q|B_L                  , .kana = "xu"      }, // ぅ
  {.key = B_Q|B_O                  , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_N                  , .kana = "xo"      }, // ぉ
  {.key = B_Q|B_DOT                , .kana = "xwa"     }, // ゎ
  {.key = B_G                      , .kana = "xtu"     }, // っ
  {.key = B_Q|B_S                  , .kana = "xke"     }, // ヶ
  {.key = B_Q|B_F                  , .kana = "xka"     }, // ヵ

  // 清音拗音 濁音拗音 半濁拗音
  {.key = B_R|B_H                  , .kana = "sya"     }, // しゃ
  {.key = B_R|B_P                  , .kana = "syu"     }, // しゅ
  {.key = B_R|B_I                  , .kana = "syo"     }, // しょ
  {.key = B_J|B_R|B_H              , .kana = "zya"     }, // じゃ
  {.key = B_J|B_R|B_P              , .kana = "zyu"     }, // じゅ
  {.key = B_J|B_R|B_I              , .kana = "zyo"     }, // じょ
  {.key = B_W|B_H                  , .kana = "kya"     }, // きゃ
  {.key = B_W|B_P                  , .kana = "kyu"     }, // きゅ
  {.key = B_W|B_I                  , .kana = "kyo"     }, // きょ
  {.key = B_J|B_W|B_H              , .kana = "gya"     }, // ぎゃ
  {.key = B_J|B_W|B_P              , .kana = "gyu"     }, // ぎゅ
  {.key = B_J|B_W|B_I              , .kana = "gyo"     }, // ぎょ
  {.key = B_G|B_H                  , .kana = "tya"     }, // ちゃ
  {.key = B_G|B_P                  , .kana = "tyu"     }, // ちゅ
  {.key = B_G|B_I                  , .kana = "tyo"     }, // ちょ
  {.key = B_J|B_G|B_H              , .kana = "dya"     }, // ぢゃ
  {.key = B_J|B_G|B_P              , .kana = "dyu"     }, // ぢゅ
  {.key = B_J|B_G|B_I              , .kana = "dyo"     }, // ぢょ
  {.key = B_D|B_H                  , .kana = "nya"     }, // にゃ
  {.key = B_D|B_P                  , .kana = "nyu"     }, // にゅ
  {.key = B_D|B_I                  , .kana = "nyo"     }, // にょ
  {.key = B_X|B_H                  , .kana = "hya"     }, // ひゃ
  {.key = B_X|B_P                  , .kana = "hyu"     }, // ひゅ
  {.key = B_X|B_I                  , .kana = "hyo"     }, // ひょ
  {.key = B_J|B_X|B_H              , .kana = "bya"     }, // びゃ
  {.key = B_J|B_X|B_P              , .kana = "byu"     }, // びゅ
  {.key = B_J|B_X|B_I              , .kana = "byo"     }, // びょ
  {.key = B_M|B_X|B_H              , .kana = "pya"     }, // ぴゃ
  {.key = B_M|B_X|B_P              , .kana = "pyu"     }, // ぴゅ
  {.key = B_M|B_X|B_I              , .kana = "pyo"     }, // ぴょ
  {.key = B_B|B_H                  , .kana = "mya"     }, // みゃ
  {.key = B_B|B_P                  , .kana = "myu"     }, // みゅ
  {.key = B_B|B_I                  , .kana = "myo"     }, // みょ
  {.key = B_E|B_H                  , .kana = "rya"     }, // りゃ
  {.key = B_E|B_P                  , .kana = "ryu"     }, // りゅ
  {.key = B_E|B_I                  , .kana = "ryo"     }, // りょ

  // 清音外来音 濁音外来音
  {.key = B_M|B_E|B_K              , .kana = "thi"     }, // てぃ
  {.key = B_M|B_E|B_P              , .kana = "thu"     }, // てゅ
  {.key = B_J|B_E|B_K              , .kana = "dhi"     }, // でぃ
  {.key = B_J|B_E|B_P              , .kana = "dhu"     }, // でゅ
  {.key = B_M|B_D|B_L              , .kana = "toxu"    }, // とぅ
  {.key = B_J|B_D|B_L              , .kana = "doxu"    }, // どぅ
  {.key = B_M|B_R|B_O              , .kana = "sye"     }, // しぇ
  {.key = B_M|B_G|B_O              , .kana = "tye"     }, // ちぇ
  {.key = B_J|B_R|B_O              , .kana = "zye"     }, // じぇ
  {.key = B_J|B_G|B_O              , .kana = "dye"     }, // ぢぇ
  {.key = B_V|B_SCLN|B_J           , .kana = "fa"      }, // ふぁ
  {.key = B_V|B_SCLN|B_K           , .kana = "fi"      }, // ふぃ
  {.key = B_V|B_SCLN|B_O           , .kana = "fe"      }, // ふぇ
  {.key = B_V|B_SCLN|B_N           , .kana = "fo"      }, // ふぉ
  {.key = B_V|B_SCLN|B_P           , .kana = "fyu"     }, // ふゅ
  {.key = B_V|B_K|B_O              , .kana = "ixe"     }, // いぇ
  {.key = B_V|B_L|B_K              , .kana = "wi"      }, // うぃ
  {.key = B_V|B_L|B_O              , .kana = "we"      }, // うぇ
  {.key = B_V|B_L|B_N              , .kana = "uxo"     }, // うぉ
  {.key = B_M|B_Q|B_J              , .kana = "va"      }, // ゔぁ
  {.key = B_M|B_Q|B_K              , .kana = "vi"      }, // ゔぃ
  {.key = B_M|B_Q|B_O              , .kana = "ve"      }, // ゔぇ
  {.key = B_M|B_Q|B_N              , .kana = "vo"      }, // ゔぉ
  {.key = B_M|B_Q|B_P              , .kana = "vuxyu"   }, // ゔゅ
  {.key = B_V|B_H|B_J              , .kana = "kuxa"    }, // くぁ
  {.key = B_V|B_H|B_K              , .kana = "kuxi"    }, // くぃ
  {.key = B_V|B_H|B_O              , .kana = "kuxe"    }, // くぇ
  {.key = B_V|B_H|B_N              , .kana = "kuxo"    }, // くぉ
  {.key = B_V|B_H|B_DOT            , .kana = "kuxwa"   }, // くゎ
  {.key = B_F|B_H|B_J              , .kana = "guxa"    }, // ぐぁ
  {.key = B_F|B_H|B_K              , .kana = "guxi"    }, // ぐぃ
  {.key = B_F|B_H|B_O              , .kana = "guxe"    }, // ぐぇ
  {.key = B_F|B_H|B_N              , .kana = "guxo"    }, // ぐぉ
  {.key = B_F|B_H|B_DOT            , .kana = "guxwa"   }, // ぐゎ
  {.key = B_V|B_L|B_J              , .kana = "tsa"     }, // つぁ

  // 追加
  {.key = B_SHFT            , .kana = " "},
  {.key = B_V|B_SHFT        , .kana = ","SS_TAP(X_ENTER)},
  {.key = B_M|B_SHFT        , .kana = "."SS_TAP(X_ENTER)},
  {.key = B_U               , .kana = SS_TAP(X_BACKSPACE)},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
  // enter+シフト(連続シフト)
  {.key = B_SHFT|B_V|B_M    , .kana = SS_TAP(X_ENTER)},

  // 非標準の変換
  {.key = B_X|B_C|B_M       , .kana = "pyu"     }, // ピュ
};

// 薙刀式のレイヤー、オンオフするキー
void set_naginata(uint8_t layer, uint16_t *onk, uint16_t *offk) {
  naginata_layer = layer;
  ngon_keys[0] = *onk;
  ngon_keys[1] = *(onk+1);
  ngoff_keys[0] = *offk;
  ngoff_keys[1] = *(offk+1);

  naginata_config.raw = eeconfig_read_user();
  if (naginata_config.os != NG_WIN && naginata_config.os != NG_MAC && naginata_config.os != NG_LINUX) {
    naginata_config.os = NG_WIN;
    naginata_config.live_conv = 1;
    naginata_config.tategaki = 1;
    naginata_config.kouchi_shift = 0;
    eeconfig_update_user(naginata_config.raw);
  }
  ng_set_unicode_mode(naginata_config.os);
}

// 薙刀式をオン
void naginata_on(void) {
  is_naginata = true;
  keycomb = 0UL;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANGUAGE_1); // Mac
  tap_code(KC_INTERNATIONAL_4); // Win
}

// 薙刀式をオフ
void naginata_off(void) {
  is_naginata = false;
  keycomb = 0UL;
  naginata_clear();
  layer_off(naginata_layer);

  tap_code(KC_LANGUAGE_2); // Mac
  tap_code(KC_INTERNATIONAL_5); // Win
}

// 薙刀式のon/off状態を返す
bool naginata_state(void) {
  return is_naginata;
}

// バッファから先頭n文字を削除する
void compress_buffer(int n) {
  if (ng_chrcount == 0) return;
  for (int j = 0; j < NGBUFFER; j++) {
    if (j + n < NGBUFFER) {
      ninputs[j] = ninputs[j + n];
    } else {
      ninputs[j] = 0;
    }
  }
  ng_chrcount -= n;
}

void switchOS(uint8_t os) {
  naginata_config.os = os;
  eeconfig_update_user(naginata_config.raw);
  ng_set_unicode_mode(naginata_config.os);
}

void ng_set_unicode_mode(uint8_t os) {
  switch (os) {
    case NG_WIN:
      set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
      break;
    case NG_MAC:
      set_unicode_input_mode(UNICODE_MODE_MACOS);
      break;
    case NG_LINUX:
      set_unicode_input_mode(UNICODE_MODE_LINUX);
      break;
  }
}

void mac_live_conversion_toggle() {
  naginata_config.live_conv ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void tategaki_toggle() {
  naginata_config.tategaki ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void kouchi_shift_toggle() {
  naginata_config.kouchi_shift ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void ng_show_os(void) {
  switch (naginata_config.os) {
    case NG_WIN:
      send_string("win");
      break;
    case NG_MAC:
      send_string("mac");
      if (naginata_config.live_conv) {
        send_string("/:lc");
      } else {
        send_string("/-lc");
      }
      break;
    case NG_LINUX:
      send_string("linux");
      break;
  }
  if (naginata_config.tategaki) {
    send_string("/tate");
  } else {
    send_string("/yoko");
  }
  if (naginata_config.kouchi_shift) {
    send_string("/:kouchi");
  } else {
    send_string("/-kouchi");
  }
}

void ng_send_unicode_string(const char *str) {
  switch (naginata_config.os) {
    case NG_LINUX:
      tap_code(KC_INTERNATIONAL_5);
      send_unicode_string(str);
      tap_code(KC_INTERNATIONAL_4);
      break;
    case NG_WIN:
      send_unicode_string(str);
      tap_code(KC_ENT);
      break;
    case NG_MAC: // Karabiner-Elementsが必要
      // TODO 未確定の文字列が残っていたら確定しておきたい
      register_code(KC_LCTL); // Unicode HEX Inputへ切り替え
      tap_code(KC_F20);
      unregister_code(KC_LCTL);
      wait_ms(UNICODE_TYPE_DELAY);
      send_unicode_string(str);
      wait_ms(UNICODE_TYPE_DELAY);
      register_code(KC_LSFT); // 日本語入力へ切り替え。再変換にならないように「shift+かな」「かな」の2打にする。
      tap_code(KC_LANGUAGE_1);
      unregister_code(KC_LSFT);
      tap_code(KC_LANGUAGE_1);
      break;
  }
}

// modifierが押されたら薙刀式レイヤーをオフしてベースレイヤーに戻す
// get_mods()がうまく動かない
static int n_modifier = 0;

bool process_modifier(uint16_t keycode, keyrecord_t *record) {
  if (IS_MODIFIER_KEYCODE(keycode) || IS_QK_MOD_TAP(keycode)) {
    if (record->event.pressed) {
      n_modifier++;
      layer_off(naginata_layer);
    } else {
      n_modifier--;
      if (n_modifier <= 0) {
        n_modifier = 0;
        layer_on(naginata_layer);
      }
    }
    return true;
  }
  return false;
}

static uint16_t fghj_buf = 0; // 押しているJかKのキーコード
static uint8_t nkeypress = 0; // 同時にキーを押している数

// 薙刀式の起動処理(COMBOを使わない)
bool enable_naginata(uint16_t keycode, keyrecord_t *record) {
  // キープレス
  if (record->event.pressed) {
    nkeypress++;
    // 1キー目、JKの前に他のキーを押していないこと
    if (fghj_buf == 0 && nkeypress == 1) {
      // かなオンキーの場合
      if (keycode == ngon_keys[0] || keycode == ngon_keys[1] || keycode == ngoff_keys[0] || keycode == ngoff_keys[1]) {
        fghj_buf = keycode;
        return false;
      }
    // ２キー目
    } else {
      // ２キー目、１キー目、両方ともかなオンキー
      if ((keycode == ngon_keys[0] && fghj_buf == ngon_keys[1]) ||
          (keycode == ngon_keys[1] && fghj_buf == ngon_keys[0])) {
        naginata_on();
        fghj_buf = 0;
        nkeypress = 0;
        return false;
      } else if ((keycode == ngoff_keys[0] && fghj_buf == ngoff_keys[1]) ||
          (keycode == ngoff_keys[1] && fghj_buf == ngoff_keys[0])) {
        naginata_off();
        fghj_buf = 0;
        nkeypress = 0;
        return false;
      // ２キー目はかなオンキーではない
      } else {
        tap_code(fghj_buf); // 1キー目を出力
        fghj_buf = 0;
        nkeypress = 0;
        return true; // 2キー目はQMKにまかせる
      }
    }
  } else {
    nkeypress = 0;
    // J/K単押しだった
    if (fghj_buf > 0) {
      tap_code(fghj_buf);
      fghj_buf = 0;

      // Shift + Jで、先にShiftを外した場合にShiftがリリースされない不具合対策
      if (IS_MODIFIER_KEYCODE(keycode)) {
        unregister_code(keycode);
      } else if (IS_QK_MOD_TAP(keycode)) {
        if (keycode & (MOD_LCTL << 8))
          unregister_code(KC_LEFT_CTRL);
        if (keycode & (MOD_LSFT << 8))
          unregister_code(KC_LEFT_SHIFT);
        if (keycode & (MOD_LALT << 8))
          unregister_code(KC_LEFT_ALT);
        if (keycode & (MOD_LGUI << 8))
          unregister_code(KC_LEFT_GUI);
        if (keycode & (MOD_RCTL << 8))
          unregister_code(KC_RIGHT_CTRL);
        if (keycode & (MOD_RSFT << 8))
          unregister_code(KC_RIGHT_SHIFT);
        if (keycode & (MOD_RALT << 8))
          unregister_code(KC_RIGHT_ALT);
        if (keycode & (MOD_RGUI << 8))
          unregister_code(KC_RIGHT_GUI);
      }
      return false;
    }
  }

  fghj_buf = 0;
  return true;
}

// バッファをクリアする
void naginata_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
  n_modifier = 0;
  nkeypress = 0;
  fghj_buf = 0;
}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {

  // まれに薙刀モードオンのまま、レイヤーがオフになることがあるので、対策
  if (n_modifier == 0 && is_naginata && !layer_state_is(naginata_layer))
    layer_on(naginata_layer);
  if (n_modifier == 0 && !is_naginata && layer_state_is(naginata_layer))
    layer_off(naginata_layer);
  if (n_modifier > 0 && layer_state_is(naginata_layer))
    layer_off(naginata_layer);

  // OS切り替え(UNICODE出力)
  if (record->event.pressed) {
    switch (keycode) {
      case NG_ON:
        naginata_on();
        return false;
        break;
      case NG_OFF:
        naginata_off();
        return false;
        break;
      case NG_CLR:
        naginata_clear();
        return false;
        break;
      case NGSW_WIN:
        switchOS(NG_WIN);
        return false;
        break;
      case NGSW_MAC:
        switchOS(NG_MAC);
        return false;
        break;
      case NGSW_LNX:
        switchOS(NG_LINUX);
        return false;
        break;
      case NG_MLV:
        mac_live_conversion_toggle();
        return false;
        break;
      case NG_SHOS:
        ng_show_os();
        return false;
        break;
      case NG_TAYO:
        tategaki_toggle();
        return false;
        break;
      case NG_KOTI:
        kouchi_shift_toggle();
        return false;
        break;
    }
  }

  if (!is_naginata)
    // return true;
    return enable_naginata(keycode, record);

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_SHFT ... NG_SHFT2:
        if (!naginata_config.kouchi_shift) {
          if (ng_chrcount >= 1) {
            naginata_type();
            keycomb = 0UL;
          }
          ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
          ng_chrcount++;
          keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
          return false;
          break;
        }
      case NG_Q ... NG_SLSH:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // 編集モードの判定
        if (keycomb == (B_D | B_F) ||
            keycomb == (B_J | B_K) ||
            keycomb == (B_C | B_V) ||
            keycomb == (B_M | B_COMM) ||
            keycomb == (B_U | B_I) ||
            keycomb == (B_E | B_R))
          is_henshu = true;
        if ((keycomb & (B_D | B_F)) != (B_D | B_F) &&
            (keycomb & (B_J | B_K)) != (B_J | B_K) &&
            (keycomb & (B_C | B_V)) != (B_C | B_V) &&
            (keycomb & (B_M | B_COMM)) != (B_M | B_COMM) &&
            (keycomb & (B_U | B_I)) != (B_U | B_I) &&
            (keycomb & (B_E | B_R)) != (B_E | B_R))
          is_henshu = false;
        // 変換候補が絞られるか、バッファが一杯になったら処理を開始
        int nc = number_of_candidates();
        if (nc == 0 || nc == 1 || ng_chrcount >= NGBUFFER) {
          naginata_type();
        }
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFT2:
        // どれかキーを離したら処理を開始する
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // 編集モードの判定
        if ((keycomb & (B_D | B_F)) != (B_D | B_F) &&
            (keycomb & (B_J | B_K)) != (B_J | B_K) &&
            (keycomb & (B_C | B_V)) != (B_C | B_V) &&
            (keycomb & (B_M | B_COMM)) != (B_M | B_COMM) &&
            (keycomb & (B_U | B_I)) != (B_U | B_I) &&
            (keycomb & (B_E | B_R)) != (B_E | B_R))
          is_henshu = false;
        if (ng_chrcount > 0) {
          naginata_type();
        }
        return false;
        break;
    }
  }
  return true;
}

// キー入力を文字に変換して出力する
void naginata_type(void) {
  // バッファの最初からnt文字目までを検索キーにする。
  // 一致する組み合わせがなければntを減らして=最後の1文字を除いて再度検索する。
  int nt = ng_chrcount;

  while (nt > 0) {
    if (naginata_lookup(nt, true)) return; // 連続シフト有効で探す
    if (naginata_lookup(nt, false)) return; // 連続シフト無効で探す
    nt--; // 最後の1キーを除いて、もう一度仮名テーブルを検索する
  }
  compress_buffer(1);
}

// 組み合わせが複数ある > 1: 変換しない
// 組み合わせが一つしかない = 1: 変換を開始する
// 組み合わせが一つしかない、ただしキーを全て押していない =-1: 変換しない
// 組み合わせがない = 0: 変換を開始する
int number_of_candidates() {
  naginata_keymap bngmap; // PROGMEM buffer
  int c = 0;
  uint32_t hit = 0;

  // keycomb_bufはバッファ内のキーの組み合わせ、keycombはリリースしたキーを含んでいない
  uint32_t keycomb_buf = 0UL;

  // バッファ内のキーを組み合わせる
  for (int i = 0; i < ng_chrcount; i++) {
    keycomb_buf |= ng_key[ninputs[i] - NG_Q];
  }

  // 通常の仮名
  for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
    memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
    if ((keycomb_buf & bngmap.key) == keycomb_buf) {
      c++;
      hit = bngmap.key;
    }
  }

  // 編集モードは積極的に確定しない
  if (is_henshu) {
    c = 2;
  }

  if (c == 1 && ng_chrcount < count_bit(hit)) {
    return -1;
  }
  return c;
}

// 押すキーの数
int count_bit(uint32_t b) {
  int c = 0;
  while (b > 0) {
    if ((b & 1UL) == 1UL) c++;
    b = b >> 1;
  }
  return c;
}

// バッファの頭からnt文字の範囲を検索キーにしてテーブル検索し、文字に変換して出力する
// 検索に成功したらtrue、失敗したらfalseを返す
bool naginata_lookup(int nt, bool shifted) {
  naginata_keymap bngmap; // PROGMEM buffer

  // keycomb_bufはバッファ内のキーの組み合わせ、keycombはリリースしたキーを含んでいない
  uint32_t keycomb_buf = 0UL;

  // バッファ内のキーを組み合わせる
  for (int i = 0; i < nt; i++) {
    keycomb_buf |= ng_key[ninputs[i] - NG_Q];
  }

  // NG_SHFT2はスペースの代わりにエンターを入力する
  if (keycomb_buf == B_SHFT && ninputs[0] == NG_SHFT2) {
    tap_code(KC_ENT);
    compress_buffer(nt);
    return true;
  }

  if (shifted) {
    // 連続シフトを有効にする
    if ((keycomb & B_SHFT) == B_SHFT) keycomb_buf |= B_SHFT;

    // 編集モードを連続する
    if ((keycomb & (B_D | B_F))    == (B_D | B_F))    keycomb_buf |= (B_D | B_F);
    if ((keycomb & (B_C | B_V))    == (B_C | B_V))    keycomb_buf |= (B_C | B_V);
    if ((keycomb & (B_J | B_K))    == (B_J | B_K))    keycomb_buf |= (B_J | B_K);
    if ((keycomb & (B_M | B_COMM)) == (B_M | B_COMM)) keycomb_buf |= (B_M | B_COMM);

    // 濁音、半濁音を連続する
    if ((keycomb & B_F) == B_F) keycomb_buf |= B_F;
    if ((keycomb & B_J) == B_J) keycomb_buf |= B_J;
    if ((keycomb & B_V) == B_V) keycomb_buf |= B_V;
    if ((keycomb & B_M) == B_M) keycomb_buf |= B_M;
  }

  if (is_henshu) {
    switch (keycomb_buf) {
      #ifdef NG_HENSHU
      case B_J|B_K|B_Q: // ^{End}
        ng_eof();
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_W: // 《》{改行}{↑}
        ng_send_unicode_string("《》");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_R: // ^s
        ng_save();
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_T: // ・
        ng_send_unicode_string("・");
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_A: // ……{改行}
        ng_send_unicode_string("……");
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_S: // (){改行}{↑}
        ng_send_unicode_string("()");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_D: // ？{改行}
        ng_send_unicode_string("？");
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_F: // 「」{改行}{↑}
        ng_send_unicode_string("「」");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_G: // 『』{改行}{↑}
        ng_send_unicode_string("『』");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_Z: // ││{改行}
        ng_send_unicode_string("││");
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_X: // 【】{改行}{↑}
        ng_send_unicode_string("【】");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_C: // ！{改行}
        ng_send_unicode_string("！");
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_V: // {改行}{↓}
        tap_code(KC_ENT);
        ng_down(1);
        compress_buffer(nt);
        return true;
        break;
      case B_J|B_K|B_B: // ／{改行}
        ng_send_unicode_string("／");
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_Y: // {Home}
        ng_home();
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_U: // +{End}{BS}
        register_code(KC_LSFT);
        ng_end();
        unregister_code(KC_LSFT);
        tap_code(KC_BSPC);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_I: // {vk1Csc079}
        ng_saihenkan();
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_O: // {Del}
        tap_code(KC_DEL);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_P: // {Esc 3}
        tap_code(KC_ESC);
        tap_code(KC_ESC);
        tap_code(KC_ESC);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_H: // {Enter}{End}
        tap_code(KC_ENT);
        ng_end();
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_J: // {↑}
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_K: // +{↑}
        register_code(KC_LSFT);
        ng_up(1);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_L: // +{↑ 7}
        register_code(KC_LSFT);
        ng_up(7);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_SCLN: // ^i
        ng_katakana();
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_N: // {End}
        ng_end();
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_M: // {↓}
        ng_down(1);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_COMM: // +{↓}
        register_code(KC_LSFT);
        ng_down(1);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_DOT: // +{↓ 7}
        register_code(KC_LSFT);
        ng_down(7);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_D|B_F|B_SLSH: // ^u
        ng_hiragana();
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_Q: // {Home}{Del 3}{BS}{←}
        ng_home();
        tap_code(KC_DEL);tap_code(KC_DEL);tap_code(KC_DEL);
        tap_code(KC_BSPC);
        ng_left(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_W: // ^x｜{改行}^v《》{改行}{↑}
        ng_cut();
        ng_send_unicode_string("｜");
        ng_paste();
        ng_send_unicode_string("《》");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_E: // {Home}{改行}{Space 3}{←}
        ng_home();
        tap_code(KC_ENT);
        tap_code(KC_SPC);
        tap_code(KC_SPC);
        tap_code(KC_SPC);
        ng_left(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_R: // {Space 3}
        tap_code(KC_SPC);
        tap_code(KC_SPC);
        tap_code(KC_SPC);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_T: // 〇{改行}
        ng_send_unicode_string("〇");
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_A: // {Home}{Del 1}{BS}{←}
        ng_home();
        tap_code(KC_DEL);
        tap_code(KC_BSPC);
        ng_left(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_S: // ^x(^v){改行}{Space}+{↑}^x
        ng_cut();
        ng_send_unicode_string("(");
        ng_paste();
        ng_send_unicode_string(")");
        tap_code(KC_SPC);
        register_code(KC_LSFT);
        ng_up(1);
        unregister_code(KC_LSFT);
        ng_cut();
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_D: // {Home}{改行}{Space 1}{←}
        ng_home();
        tap_code(KC_ENT);
        tap_code(KC_SPC);
        ng_left(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_F: // ^x「^v」{改行}{Space}+{↑}^x
        ng_cut();
        ng_send_unicode_string("「");
        ng_paste();
        ng_send_unicode_string("」");
        tap_code(KC_SPC);
        register_code(KC_LSFT);
        ng_up(1);
        unregister_code(KC_LSFT);
        ng_cut();
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_G: // ^x『^v』{改行}{Space}+{↑}^x
        ng_cut();
        ng_send_unicode_string("『");
        ng_paste();
        ng_send_unicode_string("』");
        tap_code(KC_SPC);
        register_code(KC_LSFT);
        ng_up(1);
        unregister_code(KC_LSFT);
        ng_cut();
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_Z: // 　　　×　　　×　　　×{改行 2}
        ng_send_unicode_string("　　　×　　　×　　　×");
        tap_code(KC_ENT);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_X: // ^x【^v】{改行}{Space}+{↑}^x
        ng_cut();
        ng_send_unicode_string("【");
        ng_paste();
        ng_send_unicode_string("】");
        tap_code(KC_SPC);
        register_code(KC_LSFT);
        ng_up(1);
        unregister_code(KC_LSFT);
        ng_cut();
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_C: // {改行}{End}{改行}}
        tap_code(KC_ENT);
        ng_end();
        tap_code(KC_ENT);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_V: // {改行}{End}{改行}「」{改行}{↑}
        tap_code(KC_ENT);
        ng_end();
        tap_code(KC_ENT);
        ng_send_unicode_string("「」");
        ng_up(1);
        compress_buffer(nt);
        return true;
        break;
      case B_M|B_COMM|B_B: // {End}{改行}
        ng_end();
        tap_code(KC_ENT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_Y: // +{Home}
        register_code(KC_LSFT);
        ng_home();
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_U: // ^x
        ng_cut();
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_I: // ^z
        ng_undo();
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_O: // ^y
        ng_redo();
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_P: // ^v
        ng_paste();
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_H: // ^c
        ng_copy();
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_J: // {→ 5}
        ng_right(5);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_K: // +{→}
        register_code(KC_LSFT);
        ng_right(1);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_L: // +{→ 5}
        register_code(KC_LSFT);
        ng_right(5);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_SCLN: // +{→ 20}
        register_code(KC_LSFT);
        ng_right(20);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_N: // +{End}
        register_code(KC_LSFT);
        ng_end();
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_M: // {← 5}
        ng_left(5);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_COMM: // +{←}
        register_code(KC_LSFT);
        ng_left(1);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_DOT: // +{← 5}
        register_code(KC_LSFT);
        ng_left(5);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      case B_C|B_V|B_SLSH: // +{← 20}
        register_code(KC_LSFT);
        ng_left(20);
        unregister_code(KC_LSFT);
        compress_buffer(nt);
        return true;
        break;
      #endif
// 固有名詞
      #ifdef NG_KOYUMEISHI
      case B_U|B_I|B_W: // 臨兵闘者皆陣烈在前
        ng_send_unicode_string("臨兵闘者皆陣烈在前");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_E: // 天狗
        ng_send_unicode_string("天狗");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_R: // シンイチ
        ng_send_unicode_string("シンイチ");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_T: // ネムカケ
        ng_send_unicode_string("ネムカケ");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_D: // 小鴉
        ng_send_unicode_string("小鴉");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_F: // 光太郎
        ng_send_unicode_string("光太郎");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_G: // 三神
        ng_send_unicode_string("三神");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_Z: // 火よ、在れ
        ng_send_unicode_string("火よ、在れ");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_X: // 火の剣
        ng_send_unicode_string("火の剣");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_C: // 罵詈雑
        ng_send_unicode_string("罵詈雑");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_V: // 心の闇
        ng_send_unicode_string("心の闇");
        compress_buffer(nt);
        return true;
        break;
      case B_U|B_I|B_B: // 峯
        ng_send_unicode_string("峯");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_Y: // 才一
        ng_send_unicode_string("才一");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_U: // さくら
        ng_send_unicode_string("さくら");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_I: // 酒田
        ng_send_unicode_string("酒田");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_H: // 鞍馬
        ng_send_unicode_string("鞍馬");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_J: // 青鬼
        ng_send_unicode_string("青鬼");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_K: // 百地
        ng_send_unicode_string("百地");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_SCLN: // 不動金縛りの術
        ng_send_unicode_string("不動金縛りの術");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_B: // 鬼塚
        ng_send_unicode_string("鬼塚");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_N: // 赤石
        ng_send_unicode_string("赤石");
        compress_buffer(nt);
        return true;
        break;
      case B_E|B_R|B_DOT: // 霊槍
        ng_send_unicode_string("霊槍");
        compress_buffer(nt);
        return true;
        break;
      #endif
    }
  } else {
    switch (keycomb_buf) {
      case B_T:
        ng_left(1);
        compress_buffer(nt);
        return true;
        break;
      case B_Y:
        ng_right(1);
        compress_buffer(nt);
        return true;
        break;
      case B_H|B_J:
        naginata_on();
        compress_buffer(nt);
        return true;
        break;
      case B_F|B_G:
        naginata_off();
        compress_buffer(nt);
        return true;
        break;
      // キーから仮名に変換して出力する
      // 通常の仮名
      default:
        for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
          memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
          if (keycomb_buf == bngmap.key) {
            send_string(bngmap.kana);
            compress_buffer(nt);
            return true;
          }
        }
        break;
    }
  }
  
  return false;
}

void ng_cut() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_X);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_X);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_copy() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_C);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_C);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_paste() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_V);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_V);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_up(int c) {
  if (naginata_config.tategaki) {
    for (int i = 0; i < c; i++ )
      tap_code(KC_UP);
  } else {
    for (int i = 0; i < c; i++ )
      tap_code(KC_LEFT);
  }
}

void ng_down(int c) {
  if (naginata_config.tategaki) {
    for (int i = 0; i < c; i++ )
      tap_code(KC_DOWN);
  } else {
    for (int i = 0; i < c; i++ )
      tap_code(KC_RIGHT);
  }
}

void ng_left(int c) {
  if (naginata_config.tategaki) {
    for (int i = 0; i < c; i++ )
      tap_code(KC_LEFT);
  } else {
    for (int i = 0; i < c; i++ )
      tap_code(KC_DOWN);
  }
}

void ng_right(int c) {
  if (naginata_config.tategaki) {
    for (int i = 0; i < c; i++ )
      tap_code(KC_RIGHT);
  } else {
    for (int i = 0; i < c; i++ )
      tap_code(KC_UP);
  }
}

void ng_home() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_HOME);
      break;
    case NG_MAC:
      register_code(KC_LCTL);
      tap_code(KC_A);
      unregister_code(KC_LCTL);
      break;
  }
}

void ng_end() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_END);
      break;
    case NG_MAC:
      register_code(KC_LCTL);
      tap_code(KC_E);
      unregister_code(KC_LCTL);
      break;
  }
}

void ng_katakana() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_I);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCTL);
      tap_code(KC_K);
      unregister_code(KC_LCTL);
      break;
  }
}

void ng_save() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_S);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_S);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_hiragana() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_U);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCTL);
      tap_code(KC_J);
      unregister_code(KC_LCTL);
      break;
  }
}

void ng_redo() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_Y);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_Y);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_undo() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_Z);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_Z);
      unregister_code(KC_LCMD);
      break;
  }
}

void ng_saihenkan() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_INT4);
      break;
    case NG_MAC:
      tap_code(KC_LANGUAGE_1);
      tap_code(KC_LANGUAGE_1);
      break;
  }
}

void ng_eof() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      register_code(KC_LCTL);
      tap_code(KC_END);
      unregister_code(KC_LCTL);
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      tap_code(KC_DOWN);
      unregister_code(KC_LCMD);
      break;
  }

}