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
#include "naginata.h"

#if !defined(__AVR__)
  #include <string.h>
  // #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#define NGBUFFER 10 // キー入力バッファのサイズ

#ifdef NAGINATA_TATEGAKI
  #define NGUP X_UP
  #define NGDN X_DOWN
  #define NGLT X_LEFT
  #define NGRT X_RIGHT
  #define NGKUP KC_UP
  #define NGKDN KC_DOWN
  #define NGKLT KC_LEFT
  #define NGKRT KC_RIGHT
#endif
#ifdef NAGINATA_YOKOGAKI
  #define NGUP X_LEFT
  #define NGDN X_RIGHT
  #define NGLT X_DOWN
  #define NGRT X_UP
  #define NGKUP KC_LEFT
  #define NGKDN KC_RIGHT
  #define NGKLT KC_DOWN
  #define NGKRT KC_UP
#endif

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。
static uint16_t ngon_keys[2]; // 薙刀式をオンにするキー(通常HJ)
static uint16_t ngoff_keys[2]; // 薙刀式をオフにするキー(通常FG)

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
  char kana[7];
} naginata_keymap;

// ロング
typedef struct {
  uint32_t key;
  char kana[26];
} naginata_keymap_long;

// UNICODE
typedef struct {
  uint32_t key;
  char uc[10];
} naginata_keymap_unicode;

// IME変換する文字列
typedef struct {
  uint32_t key;
  char kana[25];
} naginata_keymap_ime;

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
  {.key = B_SHFT|B_SCLN            , .kana = "tu"      }, // つ
  {.key = B_E                      , .kana = "te"      }, // て
  {.key = B_D                      , .kana = "to"      }, // と
  {.key = B_M                      , .kana = "na"      }, // な
  {.key = B_SHFT|B_D               , .kana = "ni"      }, // に
  {.key = B_SHFT|B_S               , .kana = "nu"      }, // ぬ
  {.key = B_SHFT|B_W               , .kana = "ne"      }, // ね
  {.key = B_SHFT|B_J               , .kana = "no"      }, // の
  {.key = B_C                      , .kana = "ha"      }, // は
  {.key = B_X                      , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_X               , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_DOT             , .kana = "hu"      }, // ふ
  {.key = B_P                      , .kana = "he"      }, // へ
  {.key = B_Z                      , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_Z               , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_F               , .kana = "ma"      }, // ま
  {.key = B_SHFT|B_B               , .kana = "mi"      }, // み
  {.key = B_SHFT|B_COMM            , .kana = "mu"      }, // む
  {.key = B_SHFT|B_R               , .kana = "me"      }, // め
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
  {.key = B_SHFT|B_L               , .kana = "wa"      }, // わ
  {.key = B_SHFT|B_C               , .kana = "wo"      }, // を
  {.key = B_COMM                   , .kana = "nn"      }, // ん
  {.key = B_SCLN                   , .kana = "-"       }, // ー

  // 濁音
  {.key = B_J|B_F                  , .kana = "ga"      }, // が
  {.key = B_J|B_F|B_SHFT           , .kana = "ga"      }, // が(冗長)
  {.key = B_J|B_W                  , .kana = "gi"      }, // ぎ
  {.key = B_J|B_W|B_SHFT           , .kana = "gi"      }, // ぎ(冗長)
  {.key = B_F|B_H                  , .kana = "gu"      }, // ぐ
  {.key = B_F|B_H|B_SHFT           , .kana = "gu"      }, // ぐ(冗長)
  {.key = B_J|B_S                  , .kana = "ge"      }, // げ
  {.key = B_J|B_S|B_SHFT           , .kana = "ge"      }, // げ(冗長)
  {.key = B_J|B_V                  , .kana = "go"      }, // ご
  {.key = B_J|B_V|B_SHFT           , .kana = "go"      }, // ご(冗長)
  {.key = B_F|B_U                  , .kana = "za"      }, // ざ
  {.key = B_F|B_U|B_SHFT           , .kana = "za"      }, // ざ(冗長)
  {.key = B_J|B_R                  , .kana = "zi"      }, // じ
  {.key = B_J|B_R|B_SHFT           , .kana = "zi"      }, // じ(冗長)
  {.key = B_F|B_O                  , .kana = "zu"      }, // ず
  {.key = B_F|B_O|B_SHFT           , .kana = "zu"      }, // ず(冗長)
  {.key = B_J|B_A                  , .kana = "ze"      }, // ぜ
  {.key = B_J|B_A|B_SHFT           , .kana = "ze"      }, // ぜ(冗長)
  {.key = B_J|B_B                  , .kana = "zo"      }, // ぞ
  {.key = B_J|B_B|B_SHFT           , .kana = "zo"      }, // ぞ(冗長)
  {.key = B_F|B_N                  , .kana = "da"      }, // だ
  {.key = B_F|B_N|B_SHFT           , .kana = "da"      }, // だ(冗長)
  {.key = B_J|B_G                  , .kana = "di"      }, // ぢ
  {.key = B_J|B_G|B_SHFT           , .kana = "di"      }, // ぢ(冗長)
  {.key = B_F|B_SCLN               , .kana = "du"      }, // づ
  {.key = B_F|B_SCLN|B_SHFT        , .kana = "du"      }, // づ(冗長)
  {.key = B_J|B_E                  , .kana = "de"      }, // で
  {.key = B_J|B_E|B_SHFT           , .kana = "de"      }, // で(冗長)
  {.key = B_J|B_D                  , .kana = "do"      }, // ど
  {.key = B_J|B_D|B_SHFT           , .kana = "do"      }, // ど(冗長)
  {.key = B_J|B_C                  , .kana = "ba"      }, // ば
  {.key = B_J|B_C|B_SHFT           , .kana = "ba"      }, // ば(冗長)
  {.key = B_J|B_X                  , .kana = "bi"      }, // び
  {.key = B_J|B_X|B_SHFT           , .kana = "bi"      }, // び(冗長)
  {.key = B_F|B_DOT                , .kana = "bu"      }, // ぶ
  {.key = B_F|B_DOT|B_SHFT         , .kana = "bu"      }, // ぶ(冗長)
  {.key = B_F|B_P                  , .kana = "be"      }, // べ
  {.key = B_F|B_P|B_SHFT           , .kana = "be"      }, // べ(冗長)
  {.key = B_J|B_Z                  , .kana = "bo"      }, // ぼ
  {.key = B_J|B_Z|B_SHFT           , .kana = "bo"      }, // ぼ(冗長)
  {.key = B_F|B_L                  , .kana = "vu"      }, // ゔ
  {.key = B_F|B_L|B_SHFT           , .kana = "vu"      }, // ゔ(冗長)

  // 半濁音
  {.key = B_M|B_C                  , .kana = "pa"      }, // ぱ
  {.key = B_M|B_C|B_SHFT           , .kana = "pa"      }, // ぱ(冗長)
  {.key = B_M|B_X                  , .kana = "pi"      }, // ぴ
  {.key = B_M|B_X|B_SHFT           , .kana = "pi"      }, // ぴ(冗長)
  {.key = B_V|B_DOT                , .kana = "pu"      }, // ぷ
  {.key = B_V|B_DOT|B_SHFT         , .kana = "pu"      }, // ぷ(冗長)
  {.key = B_V|B_P                  , .kana = "pe"      }, // ぺ
  {.key = B_V|B_P|B_SHFT           , .kana = "pe"      }, // ぺ(冗長)
  {.key = B_M|B_Z                  , .kana = "po"      }, // ぽ
  {.key = B_M|B_Z|B_SHFT           , .kana = "po"      }, // ぽ(冗長)

  // 小書き
  {.key = B_Q|B_H                  , .kana = "xya"     }, // ゃ
  {.key = B_Q|B_SHFT|B_H           , .kana = "xya"     }, // ゃ
  {.key = B_Q|B_P                  , .kana = "xyu"     }, // ゅ
  {.key = B_Q|B_SHFT|B_P           , .kana = "xyu"     }, // ゅ
  {.key = B_Q|B_I                  , .kana = "xyo"     }, // ょ
  {.key = B_Q|B_SHFT|B_I           , .kana = "xyo"     }, // ょ
  {.key = B_Q|B_J                  , .kana = "xa"      }, // ぁ
  {.key = B_Q|B_SHFT|B_J           , .kana = "xa"      }, // ぁ
  {.key = B_Q|B_K                  , .kana = "xi"      }, // ぃ
  {.key = B_Q|B_SHFT|B_K           , .kana = "xi"      }, // ぃ
  {.key = B_Q|B_L                  , .kana = "xu"      }, // ぅ
  {.key = B_Q|B_SHFT|B_L           , .kana = "xu"      }, // ぅ
  {.key = B_Q|B_O                  , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_SHFT|B_O           , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_N                  , .kana = "xo"      }, // ぉ
  {.key = B_Q|B_SHFT|B_N           , .kana = "xo"      }, // ぉ
  {.key = B_Q|B_L                  , .kana = "xwa"     }, // ゎ
  {.key = B_Q|B_SHFT|B_L           , .kana = "xwa"     }, // ゎ
  {.key = B_G                      , .kana = "xtu"     }, // っ

  // 清音拗音 濁音拗音 半濁拗音
  {.key = B_R|B_H                  , .kana = "sya"     }, // しゃ
  {.key = B_R|B_H|B_SHFT           , .kana = "sya"     }, // しゃ(冗長)
  {.key = B_R|B_P                  , .kana = "syu"     }, // しゅ
  {.key = B_R|B_P|B_SHFT           , .kana = "syu"     }, // しゅ(冗長)
  {.key = B_R|B_I                  , .kana = "syo"     }, // しょ
  {.key = B_R|B_I|B_SHFT           , .kana = "syo"     }, // しょ(冗長)
  {.key = B_J|B_R|B_H              , .kana = "zya"     }, // じゃ
  {.key = B_J|B_R|B_H|B_SHFT       , .kana = "zya"     }, // じゃ(冗長)
  {.key = B_J|B_R|B_P              , .kana = "zyu"     }, // じゅ
  {.key = B_J|B_R|B_P|B_SHFT       , .kana = "zyu"     }, // じゅ(冗長)
  {.key = B_J|B_R|B_I              , .kana = "zyo"     }, // じょ
  {.key = B_J|B_R|B_I|B_SHFT       , .kana = "zyo"     }, // じょ(冗長)
  {.key = B_W|B_H                  , .kana = "kya"     }, // きゃ
  {.key = B_W|B_H|B_SHFT           , .kana = "kya"     }, // きゃ(冗長)
  {.key = B_W|B_P                  , .kana = "kyu"     }, // きゅ
  {.key = B_W|B_P|B_SHFT           , .kana = "kyu"     }, // きゅ(冗長)
  {.key = B_W|B_I                  , .kana = "kyo"     }, // きょ
  {.key = B_W|B_I|B_SHFT           , .kana = "kyo"     }, // きょ(冗長)
  {.key = B_J|B_W|B_H              , .kana = "gya"     }, // ぎゃ
  {.key = B_J|B_W|B_H|B_SHFT       , .kana = "gya"     }, // ぎゃ(冗長)
  {.key = B_J|B_W|B_P              , .kana = "gyu"     }, // ぎゅ
  {.key = B_J|B_W|B_P|B_SHFT       , .kana = "gyu"     }, // ぎゅ(冗長)
  {.key = B_J|B_W|B_I              , .kana = "gyo"     }, // ぎょ
  {.key = B_J|B_W|B_I|B_SHFT       , .kana = "gyo"     }, // ぎょ(冗長)
  {.key = B_G|B_H                  , .kana = "tya"     }, // ちゃ
  {.key = B_G|B_H|B_SHFT           , .kana = "tya"     }, // ちゃ(冗長)
  {.key = B_G|B_P                  , .kana = "tyu"     }, // ちゅ
  {.key = B_G|B_P|B_SHFT           , .kana = "tyu"     }, // ちゅ(冗長)
  {.key = B_G|B_I                  , .kana = "tyo"     }, // ちょ
  {.key = B_G|B_I|B_SHFT           , .kana = "tyo"     }, // ちょ(冗長)
  {.key = B_J|B_G|B_H              , .kana = "dya"     }, // ぢゃ
  {.key = B_J|B_G|B_H|B_SHFT       , .kana = "dya"     }, // ぢゃ(冗長)
  {.key = B_J|B_G|B_P              , .kana = "dyu"     }, // ぢゅ
  {.key = B_J|B_G|B_P|B_SHFT       , .kana = "dyu"     }, // ぢゅ(冗長)
  {.key = B_J|B_G|B_I              , .kana = "dyo"     }, // ぢょ
  {.key = B_J|B_G|B_I|B_SHFT       , .kana = "dyo"     }, // ぢょ(冗長)
  {.key = B_D|B_H                  , .kana = "nya"     }, // にゃ
  {.key = B_D|B_H|B_SHFT           , .kana = "nya"     }, // にゃ(冗長)
  {.key = B_D|B_P                  , .kana = "nyu"     }, // にゅ
  {.key = B_D|B_P|B_SHFT           , .kana = "nyu"     }, // にゅ(冗長)
  {.key = B_D|B_I                  , .kana = "nyo"     }, // にょ
  {.key = B_D|B_I|B_SHFT           , .kana = "nyo"     }, // にょ(冗長)
  {.key = B_X|B_H                  , .kana = "hya"     }, // ひゃ
  {.key = B_X|B_H|B_SHFT           , .kana = "hya"     }, // ひゃ(冗長)
  {.key = B_X|B_P                  , .kana = "hyu"     }, // ひゅ
  {.key = B_X|B_P|B_SHFT           , .kana = "hyu"     }, // ひゅ(冗長)
  {.key = B_X|B_I                  , .kana = "hyo"     }, // ひょ
  {.key = B_X|B_I|B_SHFT           , .kana = "hyo"     }, // ひょ(冗長)
  {.key = B_J|B_X|B_H              , .kana = "bya"     }, // びゃ
  {.key = B_J|B_X|B_H|B_SHFT       , .kana = "bya"     }, // びゃ(冗長)
  {.key = B_J|B_X|B_P              , .kana = "byu"     }, // びゅ
  {.key = B_J|B_X|B_P|B_SHFT       , .kana = "byu"     }, // びゅ(冗長)
  {.key = B_J|B_X|B_I              , .kana = "byo"     }, // びょ
  {.key = B_J|B_X|B_I|B_SHFT       , .kana = "byo"     }, // びょ(冗長)
  {.key = B_M|B_X|B_H              , .kana = "pya"     }, // ぴゃ
  {.key = B_M|B_X|B_H|B_SHFT       , .kana = "pya"     }, // ぴゃ(冗長)
  {.key = B_M|B_X|B_P              , .kana = "pyu"     }, // ぴゅ
  {.key = B_M|B_X|B_P|B_SHFT       , .kana = "pyu"     }, // ぴゅ(冗長)
  {.key = B_M|B_X|B_I              , .kana = "pyo"     }, // ぴょ
  {.key = B_M|B_X|B_I|B_SHFT       , .kana = "pyo"     }, // ぴょ(冗長)
  {.key = B_B|B_H                  , .kana = "mya"     }, // みゃ
  {.key = B_B|B_H|B_SHFT           , .kana = "mya"     }, // みゃ(冗長)
  {.key = B_B|B_P                  , .kana = "myu"     }, // みゅ
  {.key = B_B|B_P|B_SHFT           , .kana = "myu"     }, // みゅ(冗長)
  {.key = B_B|B_I                  , .kana = "myo"     }, // みょ
  {.key = B_B|B_I|B_SHFT           , .kana = "myo"     }, // みょ(冗長)
  {.key = B_E|B_H                  , .kana = "rya"     }, // りゃ
  {.key = B_E|B_H|B_SHFT           , .kana = "rya"     }, // りゃ(冗長)
  {.key = B_E|B_P                  , .kana = "ryu"     }, // りゅ
  {.key = B_E|B_P|B_SHFT           , .kana = "ryu"     }, // りゅ(冗長)
  {.key = B_E|B_I                  , .kana = "ryo"     }, // りょ
  {.key = B_E|B_I|B_SHFT           , .kana = "ryo"     }, // りょ(冗長)

  // 清音外来音 濁音外来音
  {.key = B_M|B_E|B_K              , .kana = "thi"     }, // てぃ
  {.key = B_M|B_E|B_K|B_SHFT       , .kana = "thi"     }, // てぃ(冗長)
  {.key = B_M|B_E|B_P              , .kana = "thu"     }, // てゅ
  {.key = B_M|B_E|B_P|B_SHFT       , .kana = "thu"     }, // てゅ(冗長)
  {.key = B_J|B_E|B_K              , .kana = "dhi"     }, // でぃ
  {.key = B_J|B_E|B_K|B_SHFT       , .kana = "dhi"     }, // でぃ(冗長)
  {.key = B_J|B_E|B_P              , .kana = "dhu"     }, // でゅ
  {.key = B_J|B_E|B_P|B_SHFT       , .kana = "dhu"     }, // でゅ(冗長)
  {.key = B_M|B_D|B_L              , .kana = "toxu"    }, // とぅ
  {.key = B_M|B_D|B_L|B_SHFT       , .kana = "toxu"    }, // とぅ(冗長)
  {.key = B_J|B_D|B_L              , .kana = "doxu"    }, // どぅ
  {.key = B_J|B_D|B_L|B_SHFT       , .kana = "doxu"    }, // どぅ(冗長)
  {.key = B_M|B_R|B_O              , .kana = "sye"     }, // しぇ
  {.key = B_M|B_R|B_O|B_SHFT       , .kana = "sye"     }, // しぇ(冗長)
  {.key = B_M|B_G|B_O              , .kana = "tye"     }, // ちぇ
  {.key = B_M|B_G|B_O|B_SHFT       , .kana = "tye"     }, // ちぇ(冗長)
  {.key = B_J|B_R|B_O              , .kana = "zye"     }, // じぇ
  {.key = B_J|B_R|B_O|B_SHFT       , .kana = "zye"     }, // じぇ(冗長)
  {.key = B_J|B_G|B_O              , .kana = "dye"     }, // ぢぇ
  {.key = B_J|B_G|B_O|B_SHFT       , .kana = "dye"     }, // ぢぇ(冗長)
  {.key = B_V|B_DOT|B_J            , .kana = "fa"      }, // ふぁ
  {.key = B_V|B_DOT|B_J|B_SHFT     , .kana = "fa"      }, // ふぁ(冗長)
  {.key = B_V|B_DOT|B_K            , .kana = "fi"      }, // ふぃ
  {.key = B_V|B_DOT|B_K|B_SHFT     , .kana = "fi"      }, // ふぃ(冗長)
  {.key = B_V|B_DOT|B_O            , .kana = "fe"      }, // ふぇ
  {.key = B_V|B_DOT|B_O|B_SHFT     , .kana = "fe"      }, // ふぇ(冗長)
  {.key = B_V|B_DOT|B_N            , .kana = "fo"      }, // ふぉ
  {.key = B_V|B_DOT|B_N|B_SHFT     , .kana = "fo"      }, // ふぉ(冗長)
  {.key = B_V|B_DOT|B_P            , .kana = "fyu"     }, // ふゅ
  {.key = B_V|B_DOT|B_P|B_SHFT     , .kana = "fyu"     }, // ふゅ(冗長)
  {.key = B_V|B_K|B_O              , .kana = "ixe"     }, // いぇ
  {.key = B_V|B_K|B_O|B_SHFT       , .kana = "ixe"     }, // いぇ(冗長)
  {.key = B_V|B_L|B_K              , .kana = "wi"      }, // うぃ
  {.key = B_V|B_L|B_K|B_SHFT       , .kana = "wi"      }, // うぃ(冗長)
  {.key = B_V|B_L|B_O              , .kana = "we"      }, // うぇ
  {.key = B_V|B_L|B_O|B_SHFT       , .kana = "we"      }, // うぇ(冗長)
  {.key = B_V|B_L|B_N              , .kana = "uxo"     }, // うぉ
  {.key = B_V|B_L|B_N|B_SHFT       , .kana = "uxo"     }, // うぉ(冗長)
  {.key = B_F|B_L|B_J              , .kana = "va"      }, // ゔぁ
  {.key = B_F|B_L|B_J|B_SHFT       , .kana = "va"      }, // ゔぁ(冗長)
  {.key = B_F|B_L|B_K              , .kana = "vi"      }, // ゔぃ
  {.key = B_F|B_L|B_K|B_SHFT       , .kana = "vi"      }, // ゔぃ(冗長)
  {.key = B_F|B_L|B_O              , .kana = "ve"      }, // ゔぇ
  {.key = B_F|B_L|B_O|B_SHFT       , .kana = "ve"      }, // ゔぇ(冗長)
  {.key = B_F|B_L|B_N              , .kana = "vo"      }, // ゔぉ
  {.key = B_F|B_L|B_N|B_SHFT       , .kana = "vo"      }, // ゔぉ(冗長)
  {.key = B_F|B_L|B_P              , .kana = "vuxyu"   }, // ゔゅ
  {.key = B_F|B_L|B_P|B_SHFT       , .kana = "vuxyu"   }, // ゔゅ(冗長)
  {.key = B_V|B_H|B_J              , .kana = "kuxa"    }, // くぁ
  {.key = B_V|B_H|B_J|B_SHFT       , .kana = "kuxa"    }, // くぁ(冗長)
  {.key = B_V|B_H|B_K              , .kana = "kuxi"    }, // くぃ
  {.key = B_V|B_H|B_K|B_SHFT       , .kana = "kuxi"    }, // くぃ(冗長)
  {.key = B_V|B_H|B_O              , .kana = "kuxe"    }, // くぇ
  {.key = B_V|B_H|B_O|B_SHFT       , .kana = "kuxe"    }, // くぇ(冗長)
  {.key = B_V|B_H|B_N              , .kana = "kuxo"    }, // くぉ
  {.key = B_V|B_H|B_N|B_SHFT       , .kana = "kuxo"    }, // くぉ(冗長)
  {.key = B_V|B_H|B_L              , .kana = "kuxwa"   }, // くゎ
  {.key = B_V|B_H|B_L|B_SHFT       , .kana = "kuxwa"   }, // くゎ(冗長)
  {.key = B_F|B_H|B_J              , .kana = "guxa"    }, // ぐぁ
  {.key = B_F|B_H|B_J|B_SHFT       , .kana = "guxa"    }, // ぐぁ(冗長)
  {.key = B_F|B_H|B_K              , .kana = "guxi"    }, // ぐぃ
  {.key = B_F|B_H|B_K|B_SHFT       , .kana = "guxi"    }, // ぐぃ(冗長)
  {.key = B_F|B_H|B_O              , .kana = "guxe"    }, // ぐぇ
  {.key = B_F|B_H|B_O|B_SHFT       , .kana = "guxe"    }, // ぐぇ(冗長)
  {.key = B_F|B_H|B_N              , .kana = "guxo"    }, // ぐぉ
  {.key = B_F|B_H|B_N|B_SHFT       , .kana = "guxo"    }, // ぐぉ(冗長)
  {.key = B_F|B_H|B_L              , .kana = "guxwa"   }, // ぐゎ
  {.key = B_F|B_H|B_L|B_SHFT       , .kana = "guxwa"   }, // ぐゎ(冗長)
  {.key = B_V|B_SCLN|B_J           , .kana = "tsa"     }, // つぁ
  {.key = B_V|B_SCLN|B_J|B_SHFT    , .kana = "tsa"     }, // つぁ(冗長)
  {.key = B_V|B_SCLN|B_K           , .kana = "tsi"     }, // つぃ
  {.key = B_V|B_SCLN|B_K|B_SHFT    , .kana = "tsi"     }, // つぃ(冗長)
  {.key = B_V|B_SCLN|B_O           , .kana = "tse"     }, // つぇ
  {.key = B_V|B_SCLN|B_O|B_SHFT    , .kana = "tse"     }, // つぇ(冗長)
  {.key = B_V|B_SCLN|B_N           , .kana = "tso"     }, // つぉ
  {.key = B_V|B_SCLN|B_N|B_SHFT    , .kana = "tso"     }, // つぉ(冗長)

  // 追加
  {.key = B_SHFT            , .kana = " "},
  {.key = B_Q               , .kana = ""},
  {.key = B_V|B_SHFT        , .kana = ","},
  {.key = B_M|B_SHFT        , .kana = "."SS_TAP(X_ENTER)},
  {.key = B_U               , .kana = SS_TAP(X_BSPACE)},
  {.key = B_T               , .kana = SS_TAP(NGLT)},
  {.key = B_Y               , .kana = SS_TAP(NGRT)},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
  // enter+シフト(連続シフト)
  {.key = B_SHFT|B_V|B_M    , .kana = SS_TAP(X_ENTER)},

};

const PROGMEM naginata_keymap_long ngmapl[] = {
  {.key = B_T|B_SHFT        , .kana = SS_LSFT(SS_TAP(NGLT))},
  {.key = B_Y|B_SHFT        , .kana = SS_LSFT(SS_TAP(NGRT))},
  {.key = B_SHFT|B_T        , .kana = SS_LSFT(SS_TAP(NGLT))},
  {.key = B_SHFT|B_Y        , .kana = SS_LSFT(SS_TAP(NGRT))},

#if defined(NAGINATA_EDIT_WIN) || defined(NAGINATA_EDIT_LINUX)
// 編集モード Win
  {.key = B_J|B_K|B_Q       , .kana = SS_LCTL(SS_TAP(X_END))}, // ^{End}
//{.key = B_J|B_K|B_W       , .uc   = "｜"}, // ｜{改行}
  {.key = B_J|B_K|B_E       , .kana = "dexi"}, // /*ディ*/
  {.key = B_J|B_K|B_R       , .kana = SS_LCTL("s")}, // ^s
//{.key = B_J|B_K|B_T       , .uc   = "・"}, // ・
//{.key = B_J|B_K|B_A       , .uc   = "……"}, // ……{改行}
//{.key = B_J|B_K|B_S       , .uc   = "《"}, // 《{改行}
  {.key = B_J|B_K|B_D       , .kana = "?"SS_TAP(X_ENTER)}, // ？{改行}
//{.key = B_J|B_K|B_F       , .uc   = "「"}, // 「{改行}
//{.key = B_J|B_K|B_G       , .uc   = "("}, // ({改行}
//{.key = B_J|B_K|B_Z       , .uc   = "││"}, // ││{改行}
//{.key = B_J|B_K|B_X       , .uc   = "》"}, // 》{改行}
  {.key = B_J|B_K|B_C       , .kana = "!"SS_TAP(X_ENTER)}, // ！{改行}
//{.key = B_J|B_K|B_V       , .uc   = "」"}, // 」{改行}
//{.key = B_J|B_K|B_B       , .uc   = ")"}, // ){改行}
  {.key = B_D|B_F|B_Y       , .kana = SS_TAP(X_HOME)}, // {Home}
  {.key = B_D|B_F|B_U       , .kana = SS_LSFT(SS_TAP(X_END))SS_TAP(X_BSPACE)}, // +{End}{BS}
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_INT4)}, // {vk1Csc079}
  {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)}, // {Del}
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)}, // {Esc 3}
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_TAP(X_END)}, // {Enter}{End}
  {.key = B_D|B_F|B_J       , .kana = SS_TAP(NGUP)}, // {↑}
  {.key = B_D|B_F|B_K       , .kana = SS_LSFT(SS_TAP(NGUP))}, // +{↑}
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)}, // {↑ 5}
  {.key = B_D|B_F|B_SCLN       , .kana = SS_LCTL("i")}, // ^i
  {.key = B_D|B_F|B_N       , .kana = SS_TAP(X_END)}, // {End}
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(NGDN)}, // {↓}
  {.key = B_D|B_F|B_COMM       , .kana = SS_LSFT(SS_TAP(NGDN))}, // +{↓}
  {.key = B_D|B_F|B_DOT       , .kana = SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)}, // {↓ 5}
  {.key = B_D|B_F|B_SLSH       , .kana = SS_LCTL("u")}, // ^u
//{.key = B_M|B_COMM|B_Q       , .uc   = "／"}, // ／{改行}
//{.key = B_M|B_COMM|B_W       , .macro , // ｜{改行}{End}《》{改行}{↑}
  {.key = B_M|B_COMM|B_E       , .kana = SS_TAP(X_HOME)SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_END)}, // {Home}{改行}{Space 3}{End}
  {.key = B_M|B_COMM|B_R       , .kana = SS_TAP(X_HOME)SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_END)}, // {Home}{改行}{Space 1}{End}
//{.key = B_M|B_COMM|B_T       , .uc   = "〇"}, // 〇{改行}
//{.key = B_M|B_COMM|B_A       , .uc   = "【"}, // 【{改行}
//{.key = B_M|B_COMM|B_S       , .uc   = "〈"}, // 〈{改行}
//{.key = B_M|B_COMM|B_D       , .uc   = "『"}, // 『{改行}
//{.key = B_M|B_COMM|B_F       , .macro , // 」{改行 2}「{改行}
  {.key = B_M|B_COMM|B_G       , .kana = SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)}, // {Space 3}
//{.key = B_M|B_COMM|B_Z       , .uc   = "】"}, // 】{改行}
//{.key = B_M|B_COMM|B_X       , .uc   = "〉"}, // 〉{改行}
//{.key = B_M|B_COMM|B_C       , .uc   = "』"}, // 』{改行}
//{.key = B_M|B_COMM|B_V       , .macro , // 」{改行 2}{Space}
//{.key = B_M|B_COMM|B_B       , .macro , // 　　　×　　　×　　　×{改行 2}
  {.key = B_C|B_V|B_Y       , .kana = SS_LSFT(SS_TAP(X_HOME))}, // +{Home}
  {.key = B_C|B_V|B_U       , .kana = SS_LCTL("x")}, // ^x
  {.key = B_C|B_V|B_I       , .kana = SS_LCTL("v")}, // ^v
  {.key = B_C|B_V|B_O       , .kana = SS_LCTL("y")}, // ^y
  {.key = B_C|B_V|B_P       , .kana = SS_LCTL("z")}, // ^z
  {.key = B_C|B_V|B_H       , .kana = SS_LCTL("c")}, // ^c
  {.key = B_C|B_V|B_J       , .kana = SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)}, // {→ 5}
  {.key = B_C|B_V|B_K       , .kana = SS_LSFT(SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT))}, // +{→ 5}
  {.key = B_C|B_V|B_L       , .kana = SS_LCTL(SS_TAP(X_PGUP))}, // ^{PgUp}
  {.key = B_C|B_V|B_SCLN       , .kana = SS_LCTL(SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP))}, // ^{PgUp 5}
  {.key = B_C|B_V|B_N       , .kana = SS_LSFT(SS_TAP(X_END))}, // +{End}
  {.key = B_C|B_V|B_M       , .kana = SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)}, // {← 5}
  {.key = B_C|B_V|B_COMM       , .kana = SS_LSFT(SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT))}, // +{← 5}
  {.key = B_C|B_V|B_DOT       , .kana = SS_LCTL(SS_TAP(X_PGDOWN))}, // ^{PgDn}
  {.key = B_C|B_V|B_SLSH       , .kana = SS_LCTL(SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN))}, // ^{PgDn 5}
#endif
#ifdef NAGINATA_EDIT_MAC
// 編集モード Mac
  {.key = B_J|B_K|B_Q       , .kana = SS_LCMD(SS_LCTL("e"))}, // ^{End}
//{.key = B_J|B_K|B_W       , .kana = "nagitatesenn"}, // ｜{改行}
  {.key = B_J|B_K|B_E       , .kana = "dexi"}, // /*ディ*/
  {.key = B_J|B_K|B_R       , .kana = SS_LCMD("s")}, // ^s
//{.key = B_J|B_K|B_T       , .kana = "nagichuutenn"}, // ・
//{.key = B_J|B_K|B_A       , .kana = "nagitentenn"}, // ……{改行}
//{.key = B_J|B_K|B_S       , .kana = "nagikakkohi5"}, // 《{改行}
  {.key = B_J|B_K|B_D       , .kana = "?"SS_TAP(X_ENTER)}, // ？{改行}
//{.key = B_J|B_K|B_F       , .kana = "nagikakkohi3"}, // 「{改行}
//{.key = B_J|B_K|B_G       , .kana = "nagikakkohi6"}, // ({改行}
//{.key = B_J|B_K|B_Z       , .kana = "nagitatesenn2"}, // ││{改行}
//{.key = B_J|B_K|B_X       , .kana = "nagikakkomi5"}, // 》{改行}
  {.key = B_J|B_K|B_C       , .kana = "!"SS_TAP(X_ENTER)}, // ！{改行}
//{.key = B_J|B_K|B_V       , .kana = "nagikakkomi3"}, // 」{改行}
//{.key = B_J|B_K|B_B       , .kana = "nagikakkomi6"}, // ){改行}
  {.key = B_D|B_F|B_Y       , .kana = SS_LCTL("a")}, // {Home}
  {.key = B_D|B_F|B_U       , .kana = SS_LSFT(SS_LCTL("e"))SS_TAP(X_BSPACE)}, // +{End}{BS}
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_INT4)}, // {vk1Csc079}
  {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)}, // {Del}
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)}, // {Esc 3}
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_TAP(X_END)}, // {Enter}{End}
  {.key = B_D|B_F|B_J       , .kana = SS_TAP(NGUP)}, // {↑}
  {.key = B_D|B_F|B_K       , .kana = SS_LSFT(SS_TAP(NGUP))}, // +{↑}
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)}, // {↑ 5}
  {.key = B_D|B_F|B_SCLN       , .kana = SS_LCMD("i")}, // ^i
  {.key = B_D|B_F|B_N       , .kana = SS_LCTL("e")}, // {End}
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(NGDN)}, // {↓}
  {.key = B_D|B_F|B_COMM       , .kana = SS_LSFT(SS_TAP(NGDN))}, // +{↓}
  {.key = B_D|B_F|B_DOT       , .kana = SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)}, // {↓ 5}
  {.key = B_D|B_F|B_SLSH       , .kana = SS_LCTL("j")}, // ^u
//{.key = B_M|B_COMM|B_Q       , .kana = "naginaname"}, // ／{改行}
//{.key = B_M|B_COMM|B_W       , .macro , // ｜{改行}{End}《》{改行}{↑}
  {.key = B_M|B_COMM|B_E       , .kana = SS_LCTL("a")SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_LCTL("e")}, // {Home}{改行}{Space 3}{End}
  {.key = B_M|B_COMM|B_R       , .kana = SS_LCTL("a")SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_LCTL("e")}, // {Home}{改行}{Space 1}{End}
//{.key = B_M|B_COMM|B_T       , .kana = "nagimaru"}, // 〇{改行}
//{.key = B_M|B_COMM|B_A       , .kana = "nagikakkohi1"}, // 【{改行}
//{.key = B_M|B_COMM|B_S       , .kana = "nagikakkohi2"}, // 〈{改行}
//{.key = B_M|B_COMM|B_D       , .kana = "nagikakkohi4"}, // 『{改行}
//{.key = B_M|B_COMM|B_F       , .macro , // 」{改行 2}「{改行}
  {.key = B_M|B_COMM|B_G       , .kana = SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)}, // {Space 3}
//{.key = B_M|B_COMM|B_Z       , .kana = "nagikakkomi1"}, // 】{改行}
//{.key = B_M|B_COMM|B_X       , .kana = "nagikakkomi2"}, // 〉{改行}
//{.key = B_M|B_COMM|B_C       , .kana = "nagikakkomi4"}, // 』{改行}
//{.key = B_M|B_COMM|B_V       , .macro , // 」{改行 2}{Space}
//{.key = B_M|B_COMM|B_B       , .macro , // 　　　×　　　×　　　×{改行 2}
  {.key = B_C|B_V|B_Y       , .kana = SS_LSFT(SS_LCTL(SS_TAP(NGUP)))}, // +{Home}
  {.key = B_C|B_V|B_U       , .kana = SS_LCMD("x")}, // ^x
  {.key = B_C|B_V|B_I       , .kana = SS_LCMD("v")}, // ^v
  {.key = B_C|B_V|B_O       , .kana = SS_LCMD("y")}, // ^y
  {.key = B_C|B_V|B_P       , .kana = SS_LCMD("z")}, // ^z
  {.key = B_C|B_V|B_H       , .kana = SS_LCMD("c")}, // ^c
  {.key = B_C|B_V|B_J       , .kana = SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)}, // {→ 5}
  {.key = B_C|B_V|B_K       , .kana = SS_LSFT(SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT))}, // +{→ 5}
  {.key = B_C|B_V|B_L       , .kana = SS_TAP(X_PGUP)}, // ^{PgUp}
  {.key = B_C|B_V|B_SCLN       , .kana = SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)}, // ^{PgUp 5}
  {.key = B_C|B_V|B_N       , .kana = SS_LSFT(SS_LCTL("e"))}, // +{End}
  {.key = B_C|B_V|B_M       , .kana = SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)}, // {← 5}
  {.key = B_C|B_V|B_COMM       , .kana = SS_LSFT(SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT))}, // +{← 5}
  {.key = B_C|B_V|B_DOT       , .kana = SS_TAP(X_PGDOWN)}, // ^{PgDn}
  {.key = B_C|B_V|B_SLSH       , .kana = SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)}, // ^{PgDn 5}
#endif
};

const PROGMEM naginata_keymap_unicode ngmapu[] = {
#if defined(NAGINATA_EDIT_WIN) || defined(NAGINATA_EDIT_LINUX)
  {.key = B_J|B_K|B_W       , .uc   = "｜"}, // ｜{改行}
  {.key = B_J|B_K|B_T       , .uc   = "・"}, // ・
  {.key = B_J|B_K|B_A       , .uc   = "……"}, // ……{改行}
  {.key = B_J|B_K|B_S       , .uc   = "《"}, // 《{改行}
  {.key = B_J|B_K|B_F       , .uc   = "「"}, // 「{改行}
  {.key = B_J|B_K|B_G       , .uc   = "("}, // ({改行}
  {.key = B_J|B_K|B_Z       , .uc   = "││"}, // ││{改行}
  {.key = B_J|B_K|B_X       , .uc   = "》"}, // 》{改行}
  {.key = B_J|B_K|B_V       , .uc   = "」"}, // 」{改行}
  {.key = B_J|B_K|B_B       , .uc   = ")"}, // ){改行}
  {.key = B_M|B_COMM|B_Q       , .uc   = "／"}, // ／{改行}
  {.key = B_M|B_COMM|B_T       , .uc   = "〇"}, // 〇{改行}
  {.key = B_M|B_COMM|B_A       , .uc   = "【"}, // 【{改行}
  {.key = B_M|B_COMM|B_S       , .uc   = "〈"}, // 〈{改行}
  {.key = B_M|B_COMM|B_D       , .uc   = "『"}, // 『{改行}
  {.key = B_M|B_COMM|B_Z       , .uc   = "】"}, // 】{改行}
  {.key = B_M|B_COMM|B_X       , .uc   = "〉"}, // 〉{改行}
  {.key = B_M|B_COMM|B_C       , .uc   = "』"}, // 』{改行}

#endif
};

const PROGMEM naginata_keymap_ime ngmapi[] = {
#ifdef NAGINATA_EDIT_MAC
  {.key = B_J|B_K|B_W       , .kana = "nagitatesenn"}, // ｜{改行}
  {.key = B_J|B_K|B_T       , .kana = "nagichuutenn"}, // ・
  {.key = B_J|B_K|B_A       , .kana = "nagitentenn"}, // ……{改行}
  {.key = B_J|B_K|B_S       , .kana = "nagikakkohi5"}, // 《{改行}
  {.key = B_J|B_K|B_F       , .kana = "nagikakkohi3"}, // 「{改行}
  {.key = B_J|B_K|B_G       , .kana = "nagikakkohi6"}, // ({改行}
  {.key = B_J|B_K|B_Z       , .kana = "nagitatesenn2"}, // ││{改行}
  {.key = B_J|B_K|B_X       , .kana = "nagikakkomi5"}, // 》{改行}
  {.key = B_J|B_K|B_V       , .kana = "nagikakkomi3"}, // 」{改行}
  {.key = B_J|B_K|B_B       , .kana = "nagikakkomi6"}, // ){改行}
  {.key = B_M|B_COMM|B_Q       , .kana = "naginaname"}, // ／{改行}
  {.key = B_M|B_COMM|B_T       , .kana = "nagimaru"}, // 〇{改行}
  {.key = B_M|B_COMM|B_A       , .kana = "nagikakkohi1"}, // 【{改行}
  {.key = B_M|B_COMM|B_S       , .kana = "nagikakkohi2"}, // 〈{改行}
  {.key = B_M|B_COMM|B_D       , .kana = "nagikakkohi4"}, // 『{改行}
  {.key = B_M|B_COMM|B_Z       , .kana = "nagikakkomi1"}, // 】{改行}
  {.key = B_M|B_COMM|B_X       , .kana = "nagikakkomi2"}, // 〉{改行}
  {.key = B_M|B_COMM|B_C       , .kana = "nagikakkomi4"}, // 』{改行}
#endif
};

// 薙刀式のレイヤー、オンオフするキー
// void set_naginata(uint8_t layer) {
//   naginata_layer = layer;
// }
void set_naginata(uint8_t layer, uint16_t *onk, uint16_t *offk) {
  naginata_layer = layer;
  ngon_keys[0] = *onk;
  ngon_keys[1] = *(onk+1);
  ngoff_keys[0] = *offk;
  ngoff_keys[1] = *(offk+1);
}

// 薙刀式をオン
void naginata_on(void) {
  is_naginata = true;
  keycomb = 0UL;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

// 薙刀式をオフ
void naginata_off(void) {
  is_naginata = false;
  keycomb = 0UL;
  naginata_clear();
  layer_off(naginata_layer);

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 薙刀式のon/off状態を返す
bool naginata_state(void) {
  return is_naginata;
}

// OSのかな/英数モードをキーボードに合わせる
void makesure_mode(void) {
  if (is_naginata) {
    tap_code(KC_LANG1); // Mac
    tap_code(KC_HENK); // Win
  } else {
    tap_code(KC_LANG2); // Mac
    tap_code(KC_MHEN); // Win
  }
}

// バッファをクリアする
void naginata_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
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

#ifdef MAC_LIVE_CONVERSION
static bool is_live_conv = true;
#else
static bool is_live_conv = false;
#endif

void mac_live_conversion_toggle() {
  is_live_conv = !is_live_conv;
}

void mac_live_conversion_on() {
  is_live_conv = true;
}

void mac_live_conversion_off() {
  is_live_conv = false;
}

void mac_send_string(const char *str) {
  send_string(str);
  if (!is_live_conv) tap_code(KC_SPC);
  tap_code(KC_ENT);
}

void ng_send_unicode_string(const char *str) {
  #if defined(NAGINATA_EDIT_LINUX)
  tap_code(KC_MHEN); // Win
  send_unicode_string(str);
  tap_code(KC_HENK); // Win
  #endif
  #if defined(NAGINATA_EDIT_WIN) || defined(NAGINATA_EDIT_MAC)
  send_unicode_string(str);
  tap_code(KC_ENT);
  #endif
}

// modifierが押されたら薙刀式レイヤーをオフしてベースレイヤーに戻す
// get_mods()がうまく動かない
static int n_modifier = 0;

bool process_modifier(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
    case LCTL_T(0x01) ... LCTL_T(0xFF):
    case LSFT_T(0x01) ... LSFT_T(0xFF):
    case LALT_T(0x01) ... LALT_T(0xFF):
    case LGUI_T(0x01) ... LGUI_T(0xFF):
    case RCTL_T(0x01) ... RCTL_T(0xFF):
    case RSFT_T(0x01) ... RSFT_T(0xFF):
    case RALT_T(0x01) ... RALT_T(0xFF):
    case RGUI_T(0x01) ... RGUI_T(0xFF):
      if (record->event.pressed) {
        n_modifier++;
        layer_off(naginata_layer);
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(naginata_layer);
        }
      }
      return true;
      break;
  }
  return false;
}

static uint16_t fghj_buf = 0;

// 薙刀式の起動処理(COMBOを使わない)
bool enable_naginata(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {

    if (fghj_buf == 0 && (keycode == ngon_keys[0] || keycode == ngon_keys[1] ||
        keycode == ngoff_keys[0] || keycode == ngoff_keys[1])) {
      fghj_buf = keycode;
      return false;
    } else if (fghj_buf > 0) {
      if ((keycode == ngon_keys[0] && fghj_buf == ngon_keys[1]) ||
          (keycode == ngon_keys[1] && fghj_buf == ngon_keys[0])) {
        naginata_on();
        fghj_buf = 0;
        return false;
      } else if ((keycode == ngoff_keys[0] && fghj_buf == ngoff_keys[1]) ||
                 (keycode == ngoff_keys[1] && fghj_buf == ngoff_keys[0])) {
        naginata_off();
        fghj_buf = 0;
        return false;
      } else {
        tap_code(fghj_buf);
        fghj_buf = 0;
        return true;
      }
    }
  } else {
    if (fghj_buf > 0) {
      tap_code(fghj_buf);
      fghj_buf = 0;
      return true;
    }
  }
  fghj_buf = 0;
  return true;
}


// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata)
    // return true;
    return enable_naginata(keycode, record);

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_SHFT ... NG_SHFT2:
#ifndef NAGINATA_KOUCHI_SHIFT
        if (ng_chrcount >= 1) {
          naginata_type();
          keycomb = 0UL;
        }
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        return false;
        break;
#endif
      case NG_Q ... NG_SLSH:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // バッファが一杯になったら処理を開始
        if (ng_chrcount >= NGBUFFER) {
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

// バッファの頭からnt文字の範囲を検索キーにしてテーブル検索し、文字に変換して出力する
// 検索に成功したらtrue、失敗したらfalseを返す
bool naginata_lookup(int nt, bool shifted) {
  naginata_keymap bngmap; // PROGMEM buffer
  naginata_keymap_long bngmapl; // PROGMEM buffer
  naginata_keymap_unicode bngmapu; // PROGMEM buffer
  naginata_keymap_ime bngmapi; // PROGMEM buffer

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

  switch (keycomb_buf) {
    // send_stringできないキー、長すぎるマクロはここで定義
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
#if defined(NAGINATA_EDIT_WIN) || defined(NAGINATA_EDIT_LINUX)
    case B_M|B_COMM|B_B: //　　　×　　　×　　　×{改行 2}
      ng_send_unicode_string("　　　×　　　×　　　×");
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_W: // {改行}{End}《》{改行}{↑}
      tap_code(KC_ENT);
      tap_code(KC_END);
      ng_send_unicode_string("《》");
      tap_code(NGKUP);
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_F: // 」{改行 2}「{改行}
      ng_send_unicode_string("」");
      tap_code(KC_ENT);
      ng_send_unicode_string("「");
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_V: // 」{改行 2}{Space}
      ng_send_unicode_string("」");
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      compress_buffer(nt);
      return true;
      break;
#endif
#ifdef NAGINATA_EDIT_MAC
    case B_M|B_COMM|B_B: //　　　×　　　×　　　×{改行 2}
      mac_send_string("nagibatu");
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_W: // {改行}{End}《》{改行}{↑}
      tap_code(KC_ENT);
      tap_code(KC_END);
      mac_send_string("nagikakkohi5");
      mac_send_string("nagikakkomi5");
      tap_code(NGKUP);
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_F: // 」{改行 2}「{改行}
      mac_send_string("nagikakkomi3");
      tap_code(KC_ENT);
      mac_send_string("nagikakkohi3");
      compress_buffer(nt);
      return true;
      break;
    case B_M|B_COMM|B_V: // 」{改行 2}{Space}
      mac_send_string("nagikakkomi3");
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      compress_buffer(nt);
      return true;
      break;
#endif
    default:
      // キーから仮名に変換して出力する

      // 通常の仮名
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb_buf == bngmap.key) {
          send_string(bngmap.kana);
          compress_buffer(nt);
          return true;
        }
      }
      // 仮名ロング
      for (int i = 0; i < sizeof ngmapl / sizeof bngmapl; i++) {
        memcpy_P(&bngmapl, &ngmapl[i], sizeof(bngmapl));
        if (keycomb_buf == bngmapl.key) {
          send_string(bngmapl.kana);
          compress_buffer(nt);
          return true;
        }
      }
      // UNICODE文字
      for (int i = 0; i < sizeof ngmapu / sizeof bngmapu; i++) {
        memcpy_P(&bngmapu, &ngmapu[i], sizeof(bngmapu));
        if (keycomb_buf == bngmapu.key) {
          ng_send_unicode_string(bngmapu.uc);
          // send_unicode_hex_string(bngmapu.kana);
          // tap_code(KC_ENT);
          compress_buffer(nt);
          return true;
        }
      }
      // IME変換する文字
      for (int i = 0; i < sizeof ngmapi / sizeof bngmapi; i++) {
        memcpy_P(&bngmapi, &ngmapi[i], sizeof(bngmapi));
        if (keycomb_buf == bngmapi.key) {
          #if defined(NAGINATA_EDIT_WIN) || defined(NAGINATA_EDIT_LINUX)
          send_string(bngmapi.kana);
          #endif
          #ifdef NAGINATA_EDIT_MAC
          mac_send_string(bngmapi.kana);
          #endif
          compress_buffer(nt);
          return true;
        }
      }
  }
  return false;
}

