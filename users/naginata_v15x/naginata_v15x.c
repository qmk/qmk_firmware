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
static uint8_t keycnt = 0UL; //　押しているキーの数

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
// static uint16_t ninputs[NGBUFFER];

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


#define NKEYS 4
#define NDOUJI 3
static int kcomSize = 0;
static int combiSize[10] = {0};
static int doujiSize[10][NKEYS] = {0};

// 文字入力バッファ
static Keystroke ninputs2[NGBUFFER];
static Keystroke noutput[10][NKEYS][NDOUJI];

const int NCOMB[] = {1, 2, 5, 10};
const int COMBINDEX[] = {0, 1, 3, 8, 18};
const int COMBI[18][NKEYS][NDOUJI] = {
  // 1 key
  {{ 0, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  // 2 keys
  {{ 0, -1, -1}, { 1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  // 3 keys
  {{ 0, -1, -1}, { 1, -1, -1}, { 2, -1, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, { 2, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0, -1, -1}, { 1,  2, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, { 0,  2, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0,  1,  2}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  // 4 keys
  {{ 0, -1, -1}, { 1, -1, -1}, { 2, -1, -1}, { 3, -1, -1}},
  {{ 0,  1, -1}, { 2, -1, -1}, { 3, -1, -1}, {-1, -1, -1}},
  {{ 0, -1, -1}, { 1,  2, -1}, { 3, -1, -1}, {-1, -1, -1}},
  {{ 0, -1, -1}, { 1, -1, -1}, { 2,  3, -1}, {-1, -1, -1}},
  {{ 0,  1,  2}, { 3, -1, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, { 2,  3, -1}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0, -1, -1}, { 1,  2,  3}, {-1, -1, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, { 0,  2, -1}, { 0,  3, -1}, {-1, -1, -1}},
  {{ 0,  1, -1}, { 0,  2, -1}, { 3, -1, -1}, {-1, -1, -1}},
  {{ 0, -1, -1}, { 1,  2, -1}, { 1,  3, -1}, {-1, -1, -1}}
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
// void compress_buffer(int n) {
//   if (ng_chrcount == 0) return;
//   for (int j = 0; j < NGBUFFER; j++) {
//     if (j + n < NGBUFFER) {
//       ninputss[j] = ninputss[j + n];
//     } else {
//       ninputss[j] = 0;
//     }
//   }
//   ng_chrcount -= n;
// }

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
      tap_code(KC_LANGUAGE_2); // 未確定文字を確定する
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

// 薙刀式の起動処理(容量が大きいCOMBOを使わない)
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
  ng_chrcount = 0;
  n_modifier = 0;
  nkeypress = 0;
  fghj_buf = 0;
  keycnt = 0;
}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
  uprintf(">process_naginata, is_naginata=%u, keycode=%u, press=%u\n", is_naginata, keycode, record->event.pressed);
  #endif

  // まれに薙刀モードオンのまま、レイヤーがオフになることがあるので、対策
  if (n_modifier == 0 && is_naginata && !layer_state_is(naginata_layer))
    layer_on(naginata_layer);
  if (n_modifier == 0 && !is_naginata && layer_state_is(naginata_layer))
    layer_off(naginata_layer);
  if (n_modifier > 0 && layer_state_is(naginata_layer))
    layer_off(naginata_layer);

  // OS切り替え(UNICODE出力)
  // if (record->event.pressed) {
  //   switch (keycode) {
  //     case NG_ON:
  //       naginata_on();
  //       return false;
  //       break;
  //     case NG_OFF:
  //       naginata_off();
  //       return false;
  //       break;
  //     case NG_CLR:
  //       naginata_clear();
  //       return false;
  //       break;
  //     case NGSW_WIN:
  //       switchOS(NG_WIN);
  //       return false;
  //       break;
  //     case NGSW_MAC:
  //       switchOS(NG_MAC);
  //       return false;
  //       break;
  //     case NGSW_LNX:
  //       switchOS(NG_LINUX);
  //       return false;
  //       break;
  //     case NG_MLV:
  //       mac_live_conversion_toggle();
  //       return false;
  //       break;
  //     case NG_SHOS:
  //       ng_show_os();
  //       return false;
  //       break;
  //     case NG_TAYO:
  //       tategaki_toggle();
  //       return false;
  //       break;
  //     case NG_KOTI:
  //       kouchi_shift_toggle();
  //       return false;
  //       break;
  //   }
  // }
  if (!is_naginata)
    return enable_naginata(keycode, record);

  // if (process_modifier(keycode, record))
  //   return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_SHFT ... NG_SHFT2:
      case NG_Q ... NG_SLSH:
        keycnt++;
        ninputs2[ng_chrcount] = (Keystroke){.keycode = keycode, .pressTime = record->event.time, .releaseTime = 0}; // キー入力をバッファに貯める
        ng_chrcount++;
        if (keycnt == NKEYS) {
          naginata_type();
          ng_chrcount = 0;
        }
  #ifdef CONSOLE_ENABLE
  uprintf("<process_naginata return=false, keycnt=%u\n", keycnt);
  #endif
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFT2:  
        if (keycnt > 0)
          keycnt--;
        for (int i = 0; i < ng_chrcount; i++) {
          if (keycode == ninputs2[i].keycode) {
            ninputs2[i].releaseTime = record->event.time;
            break;
          }
        }
        // 全部キーを離したら
        if (keycnt == 0 && ng_chrcount > 0) {
          naginata_type();
          ng_chrcount = 0;
        }
  #ifdef CONSOLE_ENABLE
  uprintf("<process_naginata return=false, keycnt=%u\n", keycnt);
  #endif
        return false;
        break;
    }
  }
  #ifdef CONSOLE_ENABLE
  uprintf("<process_naginata return=true\n");
  #endif

  return true;
}

// キー入力を文字に変換して出力する
void naginata_type(void) {
  #ifdef CONSOLE_ENABLE
  uprintf(">naginata_type ng_chrcount=%u\n", ng_chrcount);
  for (int i = 0; i < ng_chrcount; i++)
    uprintf(" naginata_type key=%lu, pressTime=%lu, releaseTime=%lu\n",  ninputs2[i].keycode,  ninputs2[i].pressTime,  ninputs2[i].releaseTime);
  #endif

  naginata_keymap bngmap; // PROGMEM buffer

  //
  int n = evaluate();

  // かなへ変換する
  for (int i = 0; i < combiSize[n]; i++) {
    // バッファ内のキーを組み合わせる
    uint32_t keycomb_buf = 0UL;
    for (int j = 0; j < doujiSize[n][i]; j++) {
      keycomb_buf |= ng_key[noutput[n][i][j].keycode - NG_Q];
    }
    for (int j = 0; j < sizeof ngmap / sizeof bngmap; j++) {
      memcpy_P(&bngmap, &ngmap[j], sizeof(bngmap));
      if (keycomb_buf == bngmap.key) {
        send_string(bngmap.kana);
        #ifdef CONSOLE_ENABLE
        uprintf(" send_string %s\n", bngmap.kana);
        #endif
      }
    }
  }
  #ifdef CONSOLE_ENABLE
  uprintf("<naginata_type\n");
  #endif
}

int evaluate() {
  #ifdef CONSOLE_ENABLE
  uprintf(">evaluate ng_chrcount=%u\n", ng_chrcount);
  #endif

  // 入力 Keystrokeの1次元配列 ninputs2
  // 出力 Keystrokeの2次元配列 (同時押しの組み合わせの配列)

  kcomSize = 0;
  // combiSize[10] = {0}
  // doujiSize[10][NKEYS] = {0}

  // キー数に応じて組み合わせを選定
  // Keystroke a1[NKEYS][NDOUJI];
  // Keystroke b1[NDOUJI];
  naginata_keymap bngmap; // PROGMEM buffer

  for (int i = COMBINDEX[ng_chrcount - 1]; i < COMBINDEX[ng_chrcount]; i++) { // 組み合わせごとに
    #ifdef CONSOLE_ENABLE
    uprintf(" evaluate i=%u, kcomSize=%u\n", i, kcomSize);
    #endif
    int flag = 1; // 組み合わせが、かな辞書にあるかどうか
    int a1Size = 0;
    for (int j = 0; j < NKEYS; j++) { // 組み合わせの順番に
      #ifdef CONSOLE_ENABLE
      uprintf(" evaluate   j=%u\n", j);
      #endif
      if (COMBI[i][j][0] == -1) {
        #ifdef CONSOLE_ENABLE
        uprintf(" evaluate   j=%u, break\n", j);
        #endif
        break;
      }

      int b1Size = 0;
      for (int k = 0; k < NDOUJI; k++) { // 同時に押しているキー
        #ifdef CONSOLE_ENABLE
        uprintf(" evaluate     k=%u\n", k);
        #endif
        if (COMBI[i][j][k] == -1) {
          break;
        } else {
          // b1[b1Size++] = ninputs2[COMBI[ng_chrcount - 1][i][j][k]];
          noutput[kcomSize][j][k] = ninputs2[COMBI[i][j][k]];
          b1Size++;
        }
      }
      doujiSize[kcomSize][j] = b1Size; //あとで辞書にない可能性もあるけど、オーバーライトされるか
      #ifdef CONSOLE_ENABLE
      uprintf(" evaluate   b1Size=%u\n", b1Size);
      uprintf(" evaluate   kcomSize=%u\n", kcomSize);
      for (int k = 0; k < doujiSize[kcomSize][j]; k++) {
        uprintf(" evaluate   noutput %u,%u,%u key=%lu, pressTime=%lu, releaseTime=%lu\n", kcomSize, j, k, noutput[kcomSize][j][k].keycode,  noutput[kcomSize][j][k].pressTime,  noutput[kcomSize][j][k].releaseTime);
      }
      #endif

      // バッファ内のキーを組み合わせる
      uint32_t keycomb_buf = 0UL;
      for (int k = 0; k < b1Size; k++) {
        keycomb_buf |= ng_key[noutput[kcomSize][j][k].keycode - NG_Q];
      }
      // 辞書に存在するかチェック
      int isExist = 0;
      for (int k = 0; k < sizeof ngmap / sizeof bngmap; k++) {
        memcpy_P(&bngmap, &ngmap[k], sizeof(bngmap));
        if (keycomb_buf == bngmap.key) {
          isExist = 1;
          break;
        }
      }
      #ifdef CONSOLE_ENABLE
      uprintf(" evaluate   isExist=%u\n", isExist);
      #endif
      if (isExist) {
        // for (int k = 0; k < NDOUJI; k++) {
        //   a1[a1Size][k] = b1[k];
        // }
        a1Size++;
      } else {
        flag = 0;
        break; // 辞書になければスキップ
      }
    }
    combiSize[kcomSize] = a1Size; // a1Size++したあとでは

    // if (flag) { // 辞書にあったら登録
    //   for (int k = 0; k < combiSize[kcomSize]; k++) {
    //     for (int l = 0; l < doujiSize[kcomSize][k]; l++) {
    //       noutput[kcomSize][k][l] = a1[k][l];
    //     }
    //   }
    // }
    #ifdef CONSOLE_ENABLE
    uprintf(" evaluate flag=%u\n", flag);
    #endif
    if (flag)
      kcomSize++;
  }
  #ifdef CONSOLE_ENABLE
  uprintf(" evaluate kcomSize=%u\n", kcomSize);
  for (int i = 0; i < kcomSize; i++) {
    uprintf(" evaluate   combiSize=%u\n", combiSize[i]);
    for (int j = 0; j < combiSize[i]; j++) {
      uprintf(" evaluate     doujiSize=%u\n", doujiSize[i][j]);
      for (int k = 0; k < doujiSize[i][j]; k++) {
        uprintf(" evaluate       noutput %u,%u,%u key=%lu, pressTime=%lu, releaseTime=%lu\n", i, j, k, noutput[i][j][k].keycode,  noutput[i][j][k].pressTime,  noutput[i][j][k].releaseTime);
      }
    }
  }
  #endif
    
  // 各組み合わせの点数を求める
  double score[10];
  for (int i = 0; i < kcomSize; i++) {
    double s = 0;
    for (int j = 0; j < combiSize[i]; j++) {
      // Keystroke l[NDOUJI];
      // for (int k = 0; k < doujiSize[i][j]; k++) {
      //   l[k] = noutput[i][j][k];
      // }
      s += scoring(i, j, doujiSize[i][j]);
    }
    score[i] = s / (double)combiSize[i];
  }

  // 一番点数が高いものを返す
  double maxScore = score[0];
  int maxIndex = 0;
  for (int i = 1; i < kcomSize; i++) {
    if (score[i] > maxScore) {
      maxScore = score[i];
      maxIndex = i;
    }
  }
  #ifdef CONSOLE_ENABLE
  uprintf("<evaluate return=%u\n", maxIndex);
  #endif

  return maxIndex;
}

double scoring(int x, int y, int size) {
  #ifdef CONSOLE_ENABLE
  uprintf(">scoring size=%u\n", size);
  for (int i = 0; i < size; i++) {
    uprintf(" scoring key=%lu, pressTime=%lu, releaseTime=%lu\n", noutput[x][y][i].keycode, noutput[x][y][i].pressTime, noutput[x][y][i].releaseTime);
  }
  #endif

  if (size == 1) { // 単打の重み
  #ifdef CONSOLE_ENABLE
  uprintf("<scoring return=%u\n", (int)(0.5 * 1000));
  #endif
        return 0.8; // 単打を優先するか、同時押しを優先するかをチューニングする
    }

    // 点数=キー同士が重なる時間を、それぞれのキーを押している時間で割る
    uint32_t s2 = noutput[x][y][0].pressTime;
    uint32_t e2 = noutput[x][y][0].releaseTime;
    for (int i = 1; i < size; i++) {
        if (noutput[x][y][i].pressTime > s2) {
            s2 = noutput[x][y][i].pressTime;
        }
        if (noutput[x][y][i].releaseTime < e2) {
            e2 = noutput[x][y][i].releaseTime;
        }
    }
  #ifdef CONSOLE_ENABLE
  uprintf(" scoring s2=%lu, e2=%lu\n", s2, e2);
  #endif
    double w = (double)(e2 - s2); // キーが重なっている時間
    double s = 0.0;
    for (int i = 0; i < size; i++) {
      double pt = (double)(noutput[x][y][i].releaseTime - noutput[x][y][i].pressTime);
        s += w / pt;
    }

  #ifdef CONSOLE_ENABLE
  uprintf("<scoring return=%lu, w=%lu\n", (uint32_t)(s * 1000), (uint32_t)(w * 1000));
  #endif

    return s;
}