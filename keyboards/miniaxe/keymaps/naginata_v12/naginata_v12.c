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
  #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#define NGBUFFER 10 // キー入力バッファのサイズ

#ifdef NAGINATA_TATEGAKI
  #define NGUP X_UP
  #define NGDN X_DOWN
  #define NGLT X_LEFT
  #define NGRT X_RGHT
  #define NGKUP KC_UP
  #define NGKDN KC_DOWN
  #define NGKLT KC_LEFT
  #define NGKRT KC_RGHT
#endif
#ifdef NAGINATA_YOKOGAKI
  #define NGUP X_LEFT
  #define NGDN X_RGHT
  #define NGLT X_UP
  #define NGRT X_DOWN
  #define NGKUP KC_LEFT
  #define NGKDN KC_RGHT
  #define NGKLT KC_UP
  #define NGKRT KC_DOWN
#endif

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
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
};

// カナ変換テーブル
typedef struct {
  uint32_t key;
  char kana[7];
} naginata_keymap;

// ロング
typedef struct {
  uint32_t key;
  char kana[22];
} naginata_keymap_long;

// UNICODE
typedef struct {
  uint32_t key;
  char kana[10];
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
  {.key = B_X                      , .kana = "ke"      }, // け
  {.key = B_SHFT|B_X               , .kana = "ke"      }, // け
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
  {.key = B_S                      , .kana = "hi"      }, // ひ
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
  {.key = B_J|B_X                  , .kana = "ge"      }, // げ
  {.key = B_J|B_X|B_SHFT           , .kana = "ge"      }, // げ(冗長)
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
  {.key = B_J|B_S                  , .kana = "bi"      }, // び
  {.key = B_J|B_S|B_SHFT           , .kana = "bi"      }, // び(冗長)
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
  {.key = B_M|B_S                  , .kana = "pi"      }, // ぴ
  {.key = B_M|B_S|B_SHFT           , .kana = "pi"      }, // ぴ(冗長)
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
  // {.key = B_Q|B_SHFT|B_L           , .kana = "xu"      }, // ぅ
  {.key = B_Q|B_O                  , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_SHFT|B_O           , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_N                  , .kana = "xo"      }, // ぉ
  {.key = B_Q|B_SHFT|B_N           , .kana = "xo"      }, // ぉ
  // {.key = B_Q|B_L                  , .kana = "xwa"     }, // ゎ
  {.key = B_Q|B_SHFT|B_L           , .kana = "xwa"     }, // ゎ
  {.key = B_G                      , .kana = "xtu"     }, // っ

  // 清音拗音 濁音拗音 半濁拗音
  {.key = B_R|B_O                  , .kana = "sye"     }, // しぇ
  {.key = B_R|B_O|B_SHFT           , .kana = "sye"     }, // しぇ(冗長)
  {.key = B_R|B_H                  , .kana = "sya"     }, // しゃ
  {.key = B_R|B_H|B_SHFT           , .kana = "sya"     }, // しゃ(冗長)
  {.key = B_R|B_P                  , .kana = "syu"     }, // しゅ
  {.key = B_R|B_P|B_SHFT           , .kana = "syu"     }, // しゅ(冗長)
  {.key = B_R|B_I                  , .kana = "syo"     }, // しょ
  {.key = B_R|B_I|B_SHFT           , .kana = "syo"     }, // しょ(冗長)
  {.key = B_J|B_R|B_O              , .kana = "je"      }, // じぇ
  {.key = B_J|B_R|B_O|B_SHFT       , .kana = "je"      }, // じぇ(冗長)
  {.key = B_J|B_R|B_H              , .kana = "ja"      }, // じゃ
  {.key = B_J|B_R|B_H|B_SHFT       , .kana = "ja"      }, // じゃ(冗長)
  {.key = B_J|B_R|B_P              , .kana = "ju"      }, // じゅ
  {.key = B_J|B_R|B_P|B_SHFT       , .kana = "ju"      }, // じゅ(冗長)
  {.key = B_J|B_R|B_I              , .kana = "jo"      }, // じょ
  {.key = B_J|B_R|B_I|B_SHFT       , .kana = "jo"      }, // じょ(冗長)
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
  {.key = B_G|B_O                  , .kana = "che"     }, // ちぇ
  {.key = B_G|B_O|B_SHFT           , .kana = "che"     }, // ちぇ(冗長)
  {.key = B_G|B_H                  , .kana = "cha"     }, // ちゃ
  {.key = B_G|B_H|B_SHFT           , .kana = "cha"     }, // ちゃ(冗長)
  {.key = B_G|B_P                  , .kana = "chu"     }, // ちゅ
  {.key = B_G|B_P|B_SHFT           , .kana = "chu"     }, // ちゅ(冗長)
  {.key = B_G|B_I                  , .kana = "cho"     }, // ちょ
  {.key = B_G|B_I|B_SHFT           , .kana = "cho"     }, // ちょ(冗長)
  {.key = B_J|B_G|B_O              , .kana = "dye"     }, // ぢぇ
  {.key = B_J|B_G|B_O|B_SHFT       , .kana = "dye"     }, // ぢぇ(冗長)
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
  {.key = B_S|B_H                  , .kana = "hya"     }, // ひゃ
  {.key = B_S|B_H|B_SHFT           , .kana = "hya"     }, // ひゃ(冗長)
  {.key = B_S|B_P                  , .kana = "hyu"     }, // ひゅ
  {.key = B_S|B_P|B_SHFT           , .kana = "hyu"     }, // ひゅ(冗長)
  {.key = B_S|B_I                  , .kana = "hyo"     }, // ひょ
  {.key = B_S|B_I|B_SHFT           , .kana = "hyo"     }, // ひょ(冗長)
  {.key = B_J|B_S|B_H              , .kana = "bya"     }, // びゃ
  {.key = B_J|B_S|B_H|B_SHFT       , .kana = "bya"     }, // びゃ(冗長)
  {.key = B_J|B_S|B_P              , .kana = "byu"     }, // びゅ
  {.key = B_J|B_S|B_P|B_SHFT       , .kana = "byu"     }, // びゅ(冗長)
  {.key = B_J|B_S|B_I              , .kana = "byo"     }, // びょ
  {.key = B_J|B_S|B_I|B_SHFT       , .kana = "byo"     }, // びょ(冗長)
  {.key = B_M|B_S|B_H              , .kana = "pya"     }, // ぴゃ
  {.key = B_M|B_S|B_H|B_SHFT       , .kana = "pya"     }, // ぴゃ(冗長)
  {.key = B_M|B_S|B_P              , .kana = "pyu"     }, // ぴゅ
  {.key = B_M|B_S|B_P|B_SHFT       , .kana = "pyu"     }, // ぴゅ(冗長)
  {.key = B_M|B_S|B_I              , .kana = "pyo"     }, // ぴょ
  {.key = B_M|B_S|B_I|B_SHFT       , .kana = "pyo"     }, // ぴょ(冗長)
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
  {.key = B_M|B_E|B_K              , .kana = "texi"    }, // てぃ
  {.key = B_M|B_E|B_K|B_SHFT       , .kana = "texi"    }, // てぃ(冗長)
  {.key = B_M|B_E|B_P              , .kana = "texyu"   }, // てゅ
  {.key = B_M|B_E|B_P|B_SHFT       , .kana = "texyu"   }, // てゅ(冗長)
  {.key = B_J|B_E|B_K              , .kana = "dexi"    }, // でぃ
  {.key = B_J|B_E|B_K|B_SHFT       , .kana = "dexi"    }, // でぃ(冗長)
  {.key = B_J|B_E|B_P              , .kana = "dexyu"   }, // でゅ
  {.key = B_J|B_E|B_P|B_SHFT       , .kana = "dexyu"   }, // でゅ(冗長)
  {.key = B_M|B_D|B_L              , .kana = "toxu"    }, // とぅ
  {.key = B_M|B_D|B_L|B_SHFT       , .kana = "toxu"    }, // とぅ(冗長)
  {.key = B_J|B_D|B_L              , .kana = "doxu"    }, // どぅ
  {.key = B_J|B_D|B_L|B_SHFT       , .kana = "doxu"    }, // どぅ(冗長)
  {.key = B_M|B_R|B_O              , .kana = "sixe"    }, // しぇ
  {.key = B_M|B_R|B_O|B_SHFT       , .kana = "sixe"    }, // しぇ(冗長)
  {.key = B_M|B_G|B_O              , .kana = "tixe"    }, // ちぇ
  {.key = B_M|B_G|B_O|B_SHFT       , .kana = "tixe"    }, // ちぇ(冗長)
  {.key = B_J|B_R|B_O              , .kana = "jixe"    }, // じぇ
  {.key = B_J|B_R|B_O|B_SHFT       , .kana = "jixe"    }, // じぇ(冗長)
  {.key = B_J|B_G|B_O              , .kana = "dixe"    }, // ぢぇ
  {.key = B_J|B_G|B_O|B_SHFT       , .kana = "dixe"    }, // ぢぇ(冗長)
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
  {.key = B_V|B_L|B_K              , .kana = "uxi"     }, // うぃ
  {.key = B_V|B_L|B_K|B_SHFT       , .kana = "uxi"     }, // うぃ(冗長)
  {.key = B_V|B_L|B_O              , .kana = "uxe"     }, // うぇ
  {.key = B_V|B_L|B_O|B_SHFT       , .kana = "uxe"     }, // うぇ(冗長)
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
  {.key = B_V|B_SCLN|B_J           , .kana = "tuxa"    }, // つぁ
  {.key = B_V|B_SCLN|B_J|B_SHFT    , .kana = "tuxa"    }, // つぁ(冗長)
  {.key = B_V|B_SCLN|B_K           , .kana = "tuxi"    }, // つぃ
  {.key = B_V|B_SCLN|B_K|B_SHFT    , .kana = "tuxi"    }, // つぃ(冗長)
  {.key = B_V|B_SCLN|B_O           , .kana = "tuxe"    }, // つぇ
  {.key = B_V|B_SCLN|B_O|B_SHFT    , .kana = "tuxe"    }, // つぇ(冗長)
  {.key = B_V|B_SCLN|B_N           , .kana = "tuxo"    }, // つぉ
  {.key = B_V|B_SCLN|B_N|B_SHFT    , .kana = "tuxo"    }, // つぉ(冗長)

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

  // 編集モード1
#ifdef NAGINATA_EDIT_WIN
  // {.key = B_J|B_K|B_Q       , .kana = ""},
  // {.key = B_J|B_K|B_W       , .kana = ""},
  {.key = B_J|B_K|B_E       , .kana = "dexi"},
  {.key = B_J|B_K|B_R       , .kana = SS_LCTRL("s")},
  {.key = B_J|B_K|B_T       , .kana = SS_LCTRL("c")},

  {.key = B_D|B_F|B_Y       , .kana = SS_TAP(X_HOME)},
  // {.key = B_D|B_F|B_U       , .kana = ""},
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_INT4)}, // 再変換
  {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)},
  // {.key = B_D|B_F|B_P       , .kana = ""},

  {.key = B_J|B_K|B_A       , .kana = SS_TAP(X_PGDOWN)},
  {.key = B_J|B_K|B_S       , .kana = SS_TAP(X_PGUP)},
  // {.key = B_J|B_K|B_D       , .kana = SS_TAP(X_MS_WH_UP)}, // wheel up
  // {.key = B_J|B_K|B_F       , .kana = SS_TAP(X_MS_WH_DOWN)}, // wheel down
  {.key = B_J|B_K|B_G       , .kana = SS_LCTRL("x")},
  // {.key = B_J|B_K|B_H       , .kana = ""},

  {.key = B_D|B_F|B_J       , .kana = SS_TAP(NGUP)},
  // {.key = B_D|B_F|B_K       , .kana = ""},
  // {.key = B_D|B_F|B_L       , .kana = ""},
  {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("i")}, // カタカナ変換

  {.key = B_J|B_K|B_Z       , .kana = SS_LCTRL("z")},
  // {.key = B_J|B_K|B_X       , .kana = ""}, // 確定UNDO
  {.key = B_J|B_K|B_C       , .kana = SS_TAP(NGLT)SS_TAP(NGLT)},
  {.key = B_J|B_K|B_V       , .kana = SS_TAP(NGRT)SS_TAP(NGRT)},
  {.key = B_J|B_K|B_B       , .kana = SS_LCTRL("v")},

  {.key = B_D|B_F|B_N       , .kana = SS_TAP(X_END)},
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(NGDN)},
  // {.key = B_D|B_F|B_COMM       , .kana = ""},
  // {.key = B_D|B_F|B_DOT       , .kana = ""},
  {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("u")}, // ひらがな変換
#endif
#ifdef NAGINATA_EDIT_MAC
  // {.key = B_J|B_K|B_Q       , .kana = ""},
  // {.key = B_J|B_K|B_W       , .kana = ""},
  {.key = B_J|B_K|B_E       , .kana = "dexi"},
  {.key = B_J|B_K|B_R       , .kana = SS_LGUI("s")},
  {.key = B_J|B_K|B_T       , .kana = SS_LGUI("c")},

  // {.key = B_D|B_F|B_Y       , .kana = ""},
  // {.key = B_D|B_F|B_U       , .kana = ""},
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_LANG1)SS_TAP(X_LANG1)},
  {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)},
  // {.key = B_D|B_F|B_P       , .kana = ""},

  {.key = B_J|B_K|B_A       , .kana = SS_TAP(X_PGDOWN)},
  {.key = B_J|B_K|B_S       , .kana = SS_TAP(X_PGUP)},
  // {.key = B_J|B_K|B_D       , .kana = ""},
  // {.key = B_J|B_K|B_F       , .kana = ""},
  {.key = B_J|B_K|B_G       , .kana = SS_LGUI("x")},

  // {.key = B_D|B_F|B_H       , .kana = ""},
  {.key = B_D|B_F|B_J       , .kana = SS_TAP(NGUP)},
  // {.key = B_D|B_F|B_K       , .kana = ""},
  // {.key = B_D|B_F|B_L       , .kana = ""},
  {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("k")},

  {.key = B_J|B_K|B_Z       , .kana = SS_LGUI("z")},
  {.key = B_J|B_K|B_X       , .kana = ""}, // 確定UNDO
  {.key = B_J|B_K|B_C       , .kana = SS_TAP(NGLT)SS_TAP(NGLT)},
  {.key = B_J|B_K|B_V       , .kana = SS_TAP(NGRT)SS_TAP(NGRT)},
  {.key = B_J|B_K|B_B       , .kana = SS_LGUI("v")},

  // {.key = B_D|B_F|B_N       , .kana = ""},
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(NGDN)},
  // {.key = B_D|B_F|B_COMM    , .kana = ""},
  // {.key = B_D|B_F|B_DOT     , .kana = ""},
  {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("j")},
#endif

  // 編集モード2
  {.key = B_M|B_COMM|B_D    , .kana = "!"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_F    , .kana = "?"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_B    , .kana = "   "},

};

const PROGMEM naginata_keymap_long ngmapl[] = {
  {.key = B_T|B_SHFT        , .kana = SS_LSFT(SS_TAP(NGLT))},
  {.key = B_Y|B_SHFT        , .kana = SS_LSFT(SS_TAP(NGRT))},
  {.key = B_SHFT|B_T        , .kana = SS_LSFT(SS_TAP(NGLT))},
  {.key = B_SHFT|B_Y        , .kana = SS_LSFT(SS_TAP(NGRT))},

  // 編集モード1
#ifdef NAGINATA_EDIT_WIN
  {.key = B_J|B_K|B_Q       , .kana = SS_LCTRL(SS_TAP(X_END))},
  {.key = B_J|B_K|B_W       , .kana = SS_LCTRL(SS_TAP(X_HOME))},
  // {.key = B_J|B_K|B_E       , .kana = ""},
  // {.key = B_J|B_K|B_R       , .kana = ""},
  // {.key = B_J|B_K|B_T       , .kana = ""},

  // {.key = B_D|B_F|B_Y       , .kana = ""},
  {.key = B_D|B_F|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_END)SS_UP(X_LSHIFT)SS_TAP(X_BSPACE)},
  // {.key = B_D|B_F|B_I       , .kana = ""},
  // {.key = B_D|B_F|B_O       , .kana = ""},
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)},

  // {.key = B_J|B_K|B_A       , .kana = ""},
  // {.key = B_J|B_K|B_S       , .kana = ""},
  {.key = B_J|B_K|B_D       , .kana = SS_TAP(X_MS_WH_UP)SS_TAP(X_MS_WH_UP)SS_TAP(X_MS_WH_UP)}, // wheel up
  {.key = B_J|B_K|B_F       , .kana = SS_TAP(X_MS_WH_DOWN)SS_TAP(X_MS_WH_DOWN)SS_TAP(X_MS_WH_DOWN)}, // wheel down
  // {.key = B_J|B_K|B_G       , .kana = ""},

  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_TAP(X_END)},
  // {.key = B_D|B_F|B_J       , .kana = ""},
  {.key = B_D|B_F|B_K       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(NGUP)SS_UP(X_LSHIFT)},
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)},
  // {.key = B_D|B_F|B_SCLN    , .kana = ""},

  // {.key = B_J|B_K|B_Z       , .kana = ""},
  {.key = B_J|B_K|B_X       , .kana = SS_LCTRL("X_BSPACE")}, // 確定UNDO
  // {.key = B_J|B_K|B_C       , .kana = ""},
  // {.key = B_J|B_K|B_V       , .kana = ""},
  // {.key = B_J|B_K|B_B       , .kana = ""},

  // {.key = B_D|B_F|B_N       , .kana = ""},
  // {.key = B_D|B_F|B_M       , .kana = ""},
  {.key = B_D|B_F|B_COMM    , .kana = SS_LSFT(SS_TAP(NGDN))},
  {.key = B_D|B_F|B_DOT     , .kana = SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)},
  // {.key = B_D|B_F|B_SLSH    , .kana = ""},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_J|B_K|B_Q       , .kana = SS_LCMD(SS_TAP(X_DOWN))},
  {.key = B_J|B_K|B_W       , .kana = SS_LCMD(SS_TAP(X_UP))},
  // {.key = B_J|B_K|B_E       , .kana = ""},
  // {.key = B_J|B_K|B_R       , .kana = ""},
  // {.key = B_J|B_K|B_T       , .kana = ""},

  {.key = B_D|B_F|B_Y       , .kana = SS_LCMD(SS_TAP(NGUP))}, // 行頭
  {.key = B_D|B_F|B_U       , .kana = SS_LSFT(SS_LCMD(SS_TAP(NGDN)))SS_LGUI("x")},
  // {.key = B_D|B_F|B_I       , .kana = ""},
  // {.key = B_D|B_F|B_O       , .kana = ""},
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)},

  // {.key = B_J|B_K|B_A       , .kana = ""},
  // {.key = B_J|B_K|B_S       , .kana = ""},
  {.key = B_J|B_K|B_D       , .kana = SS_TAP(X_MS_WH_UP)SS_TAP(X_MS_WH_UP)SS_TAP(X_MS_WH_UP)}, // wheel up
  {.key = B_J|B_K|B_F       , .kana = SS_TAP(X_MS_WH_DOWN)SS_TAP(X_MS_WH_DOWN)SS_TAP(X_MS_WH_DOWN)}, // wheel down
  // {.key = B_J|B_K|B_G       , .kana = ""},

  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_LCMD(SS_TAP(NGDN))},
  // {.key = B_D|B_F|B_J       , .kana = ""},
  {.key = B_D|B_F|B_K       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(NGUP)SS_UP(X_LSHIFT)},
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)},
  // {.key = B_D|B_F|B_SCLN    , .kana = ""},

  // {.key = B_J|B_K|B_Z       , .kana = ""},
  // {.key = B_J|B_K|B_X       , .kana = ""},
  // {.key = B_J|B_K|B_C       , .kana = ""},
  // {.key = B_J|B_K|B_V       , .kana = ""},
  // {.key = B_J|B_K|B_B       , .kana = ""},

  {.key = B_D|B_F|B_N       , .kana = SS_LCMD(SS_TAP(NGDN))}, // 行末
  // {.key = B_D|B_F|B_M       , .kana = ""},
  {.key = B_D|B_F|B_COMM    , .kana = SS_LSFT(SS_TAP(NGDN))},
  {.key = B_D|B_F|B_DOT     , .kana = SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)},
  // {.key = B_D|B_F|B_SLSH    , .kana = ""},
#endif

  // 編集モード2
#ifdef NAGINATA_EDIT_WIN
  {.key = B_M|B_COMM|B_G    , .kana = SS_TAP(X_HOME)"   "SS_TAP(X_END)},
  {.key = B_C|B_V|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_HOME)SS_UP(X_LSHIFT)SS_LCTRL("x")},
#endif

};

const PROGMEM naginata_keymap_unicode ngmapu[] = {
  // 編集モード2
#ifdef NAGINATA_EDIT_WIN
  {.key = B_M|B_COMM|B_Q    , .kana = "FF0F"}, // ／
  {.key = B_M|B_COMM|B_W    , .kana = "FF1A"}, // ：
  {.key = B_M|B_COMM|B_R    , .kana = "3007"}, // 〇

  {.key = B_C|B_V|B_I       , .kana = "30FB"}, // ・
  {.key = B_C|B_V|B_O       , .kana = "FF5C"}, // ｜

  {.key = B_M|B_COMM|B_A    , .kana = "3010"}, // 【
  {.key = B_M|B_COMM|B_S    , .kana = "3008"}, // 〈

  {.key = B_C|B_V|B_J       , .kana = "300C"}, // 「
  {.key = B_C|B_V|B_K       , .kana = "300E"}, // 『
  {.key = B_C|B_V|B_L       , .kana = "300A"}, // 《
  {.key = B_C|B_V|B_SCLN    , .kana = "FF08"}, // （

  {.key = B_M|B_COMM|B_Z    , .kana = "3011"}, // 】
  {.key = B_M|B_COMM|B_X    , .kana = "3009"}, // 〉
  {.key = B_M|B_COMM|B_C    , .kana = "2026 2026"}, // ……
  {.key = B_M|B_COMM|B_V    , .kana = "2500 2500"}, // ──

  {.key = B_C|B_V|B_M       , .kana = "300D"}, // 」
  {.key = B_C|B_V|B_COMM    , .kana = "300F"}, // 』
  {.key = B_C|B_V|B_DOT     , .kana = "300B"}, // 》
  {.key = B_C|B_V|B_SLSH    , .kana = "FF09"}, // ）
#endif
};

const PROGMEM naginata_keymap_ime ngmapi[] = {
  // 編集モード2
#ifdef NAGINATA_EDIT_MAC
  {.key = B_M|B_COMM|B_Q    , .kana = "naginaname"}, // ／
  {.key = B_M|B_COMM|B_W    , .kana = ":"}, // ：
  {.key = B_M|B_COMM|B_E    , .kana = "nagibatu"}, // xxx
  {.key = B_M|B_COMM|B_R    , .kana = "nagimaru"}, // 〇

  {.key = B_C|B_V|B_I       , .kana = "nagichuutenn"}, // ・
  {.key = B_C|B_V|B_O       , .kana = "nagitatesenn"}, // ｜

  {.key = B_M|B_COMM|B_A    , .kana = "nagikakkohi1"}, // 【
  {.key = B_M|B_COMM|B_S    , .kana = "nagikakkohi2"}, // 〈

  {.key = B_C|B_V|B_J       , .kana = "nagikakkohi3"}, // 「
  {.key = B_C|B_V|B_K       , .kana = "nagikakkohi4"}, // 『
  {.key = B_C|B_V|B_L       , .kana = "nagikakkohi5"}, // 《
  {.key = B_C|B_V|B_SCLN    , .kana = "nagikakkohi6"}, // （

  {.key = B_M|B_COMM|B_Z    , .kana = "nagikakkomi1"}, // 】
  {.key = B_M|B_COMM|B_X    , .kana = "nagikakkomi2"}, // 〉
  {.key = B_M|B_COMM|B_C    , .kana = "nagitentenn"}, // ……
  {.key = B_M|B_COMM|B_V    , .kana = "nagisensenn"}, // ──

  {.key = B_C|B_V|B_M       , .kana = "nagikakkomi3"}, // 」
  {.key = B_C|B_V|B_COMM    , .kana = "nagikakkomi4"}, // 』
  {.key = B_C|B_V|B_DOT     , .kana = "nagikakkomi5"}, // 》
  {.key = B_C|B_V|B_SLSH    , .kana = "nagikakkomi6"}, // ）

  {.key = B_M|B_COMM|B_T    , .kana = SS_LCMD(SS_TAP(NGUP))" "SS_LCMD(SS_TAP(X_RIGHT))},
  {.key = B_M|B_COMM|B_G    , .kana = SS_LCMD(SS_TAP(NGUP))"   "SS_LCMD(SS_TAP(X_RIGHT))},
  {.key = B_C|B_V|B_U       , .kana = SS_LSFT(SS_LCMD(SS_TAP(NGUP)))SS_LGUI("x")},
#endif
};

// 薙刀式のレイヤー、シフトキーを設定
void set_naginata(uint8_t layer) {
  naginata_layer = layer;
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

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata) return true;

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_Q ... NG_SHFT:
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
      case NG_Q ... NG_SHFT:
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
#ifdef NAGINATA_EDIT_WIN
    case B_M|B_COMM|B_E: //    x   x   x ENT ENT
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
          send_unicode_hex_string("3000"); // 全角スペース
        send_unicode_hex_string("00D7"); // ×
      }
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_P: // ここから末までふりがな定義
      send_unicode_hex_string("FF5C");
      tap_code(KC_ENT);
      tap_code(KC_END);
      send_unicode_hex_string("300A 300B");
      tap_code(KC_ENT);
      tap_code(KC_LEFT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_Y: // 会話とじ次段落
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_H: // 会話とじ次ひらき
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      send_unicode_hex_string("300C");
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_N: // 会話とじ次行の文
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
#endif
#ifdef NAGINATA_EDIT_MAC
    case B_C|B_V|B_P: // ここから末までふりがな定義
      mac_send_string("nagitatesenn");
      tap_code(KC_ENT);
      tap_code(KC_END);
      mac_send_string("nagikakkohi5");
      mac_send_string("nagikakkomi5");
      tap_code(KC_LEFT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_Y: // 会話とじ次段落
      mac_send_string("nagikakkomi3");
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_H: // 会話とじ次ひらき
      mac_send_string("nagikakkomi3");
      tap_code(KC_ENT);
      mac_send_string("nagikakkohi3");
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_N: // 会話とじ次行の文
      mac_send_string("nagikakkomi3");
      tap_code(KC_ENT);
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
          send_unicode_hex_string(bngmapu.kana);
          tap_code(KC_ENT);
          compress_buffer(nt);
          return true;
        }
      }
      // IME変換する文字
      for (int i = 0; i < sizeof ngmapi / sizeof bngmapi; i++) {
        memcpy_P(&bngmapi, &ngmapi[i], sizeof(bngmapi));
        if (keycomb_buf == bngmapi.key) {
          mac_send_string(bngmapi.kana);
          compress_buffer(nt);
          return true;
        }
      }
  }
  return false;
}

